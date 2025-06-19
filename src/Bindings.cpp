#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/pytypes.h>

#include "WinApi.h"
#include "Process.h"

namespace py = pybind11;

Process attach(const uint32_t pid)
{
	return Process(windows::open_process(pid));
}

PYBIND11_MODULE(_core, m) {
	m.def("attach", &attach, py::arg("pid"));
	py::class_<Process>(m, "Process")
		.def(
			"read",
			[](const Process& self, std::uintptr_t address, size_t size) {
				auto buffer = self.read(reinterpret_cast<void*>(address), size);
				return py::bytes(reinterpret_cast<char*>(buffer.data()), buffer.size());
			},
			py::arg("address"),
			py::arg("size")
		)
		.def(
			"write",
			[](const Process& self, std::uintptr_t address, py::bytes buffer) {
				std::string buffer_string = buffer;
				self.write(
					reinterpret_cast<void*>(address),
					std::span<std::byte>(
						reinterpret_cast<std::byte*>(buffer_string.data()),
						buffer_string.size()
					)
				);
			},
			py::arg("address"),
			py::arg("data")
		)
		.def(
			"find_memory_regions",
			&Process::find_memory_regions
		)
		.def(
			"search_bytes",
			[](const Process& self, py::bytes pattern) {
				std::string pattern_string = pattern;
				return self.search_bytes(
					std::span<std::byte>(
						reinterpret_cast<std::byte*>(pattern_string.data()),
						pattern_string.size()
					)
				);
			},
			py::arg("pattern")
		);

	py::enum_<MemoryRegionType>(m, "MemoryRegionType")
		.value("PRIVATE", MemoryRegionType::PRIVATE)
		.value("IMAGE", MemoryRegionType::IMAGE)
		.value("MAPPED", MemoryRegionType::MAPPED)
		.value("UNDEFINED", MemoryRegionType::UNDEFINED);

	py::enum_<MemoryRegionState>(m, "MemoryRegionState")
		.value("FREE", MemoryRegionState::FREE)
		.value("RESERVED", MemoryRegionState::RESERVED)
		.value("COMMITED", MemoryRegionState::COMMITED);

	py::class_<MemoryRegion>(m, "MemoryRegion")
		.def_property_readonly("base_address", &MemoryRegion::base_address)
		.def_property_readonly("size", &MemoryRegion::size)
		.def_property_readonly("type", &MemoryRegion::type)
		.def_property_readonly("state", &MemoryRegion::state)
		.def_property_readonly("protection_flags", &MemoryRegion::protection_flags);
}
