#pragma once

#include <vector>
#include <span>

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
}
