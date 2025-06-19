#pragma once

#include <vector>
#include <span>
#include <cstddef>

namespace memory_search {
    // Returns all indices of buffer in which pattern matches
    std::vector<size_t> all_matching_sequences(
        std::span<const std::byte> buffer,
        std::span<const std::byte> pattern
    );
};
