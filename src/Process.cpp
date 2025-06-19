#include "Process.h"

#include "Exceptions.h"
#include "WinApi.h"
#include "MemorySearch.h"

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

std::vector<std::uintptr_t> Process::search_bytes(const std::span<const std::byte> pattern) const
{
	std::vector<std::uintptr_t> matching_addresses{};
	const auto memory_regions = find_memory_regions();

	for (const auto& region : memory_regions) {
		if (region.is_readable()) {
			const auto region_data = windows::read_process_memory(
				m_process_handle.get(),
				reinterpret_cast<const void*>(region.base_address()),
				region.size()
			);
			const auto matches = memory_search::all_matching_sequences(std::span(region_data), pattern);
			for (const auto& match : matches) {
				matching_addresses.emplace_back(region.base_address() + match);
			}
		}
	}
	return matching_addresses;
}
