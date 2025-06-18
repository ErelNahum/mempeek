#pragma once

#include <vector>
#include <span>

#include <Windows.h>

#include "Guards.h"

namespace windows
{
    HandleGuard open_process(uint32_t pid);
    std::vector<std::byte> read_process_memory(
        void* process_handle,
        const void* address,
        size_t size
    );

    void write_process_memory(
        void* process_handle,
        void* address,
        std::span<const std::byte> buffer
    );

    SYSTEM_INFO get_system_info();

    MEMORY_BASIC_INFORMATION virtual_query_ex(
        void* process_handle,
        const void* address
    );
}
