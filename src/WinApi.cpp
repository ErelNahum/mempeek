#include "WinApi.h"

#include <Windows.h>

#include "Exceptions.h"

HandleGuard windows::open_process(uint32_t pid)
{
    const auto process_handle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    if (nullptr == process_handle) {
        THROW_WINDOWS_EXCEPTION();
    }
    return HandleGuard(process_handle);
}

std::vector<std::byte> windows::read_process_memory(
    void* const process_handle,
    const void* const address,
    const size_t size
)
{
    std::vector<std::byte> buffer(size);
    size_t number_of_bytes_read = 0;
    if (
        !ReadProcessMemory(
            process_handle,
            address,
            buffer.data(),
            size,
            &number_of_bytes_read
        )
        || number_of_bytes_read != size
    ) {
        THROW_WINDOWS_EXCEPTION();
    }
    return buffer;
}

void windows::write_process_memory(
    void* const process_handle,
    void* const address,
    const std::span<const std::byte> buffer
)
{
    size_t number_of_bytes_written = 0;
    if (
        !WriteProcessMemory(
            process_handle,
            address,
            buffer.data(),
            buffer.size(),
            &number_of_bytes_written
        )
        || number_of_bytes_written != buffer.size()
    ) {
        THROW_WINDOWS_EXCEPTION();
    }
}

SYSTEM_INFO windows::get_system_info()
{
    SYSTEM_INFO system_info{};
    GetSystemInfo(&system_info);
    return system_info;
}

MEMORY_BASIC_INFORMATION windows::virtual_query_ex(
    void* const process_handle,
    const void* const address
)
{
    MEMORY_BASIC_INFORMATION memory_information{};
    if (
        !VirtualQueryEx(
            process_handle,
            address,
            &memory_information,
            sizeof(memory_information)
        )
    ) {
        THROW_WINDOWS_EXCEPTION();
    }
    return memory_information;
}
