#include "Process.h"

#include <iostream>

#include "Exceptions.h"
#include "WinApi.h"

Process::Process(HandleGuard&& process_handle)
	: m_process_handle{std::move(process_handle)} {}

std::vector<std::byte> Process::read(
	const void* const address,
	const size_t size
) const
{
	return windows::read_process_memory(m_process_handle.get(), address, size);
}

void Process::write(void* const address, std::span<const std::byte> data) const
{
	windows::write_process_memory(m_process_handle.get(), address, data);
}

std::vector<MemoryRegion> Process::find_memory_regions() const
{
	const auto system_info = windows::get_system_info();
	auto address = reinterpret_cast<std::uintptr_t>(system_info.lpMinimumApplicationAddress);
	const auto end_address = reinterpret_cast<std::uintptr_t>(system_info.lpMaximumApplicationAddress);

	std::vector<MemoryRegion> memory_regions{};
	while (address < end_address) {
		try {
			const auto region_information = windows::virtual_query_ex(
				m_process_handle.get(),
				reinterpret_cast<void*>(address)
			);
			memory_regions.emplace_back(region_information);
			address += region_information.RegionSize;
		} catch (const WindowsException& exception) {
			address += system_info.dwPageSize;
		}
	}
	return memory_regions;
}
