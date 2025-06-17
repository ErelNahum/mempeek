#include "Process.h"

#include "Exceptions.h"
#include "WinApi.h"

Process::Process(HandleGuard&& process_handle)
	: m_process_handle(std::move(process_handle)) {}

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
