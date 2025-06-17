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
		);
}
