#include "MemorySearch.h"

#include <algorithm>

std::vector<size_t> memory_search::all_matching_sequences(
    const std::span<const std::byte> buffer,
    const std::span<const std::byte> pattern
)
{
    std::vector<size_t> matches{};
    auto it = std::search(buffer.cbegin(), buffer.cend(), pattern.cbegin(), pattern.cend());
    while (it != buffer.cend()) {
        matches.emplace_back(std::distance(buffer.cbegin(), it));
        it = std::search(it + 1 , buffer.cend(), pattern.cbegin(), pattern.cend());
    }
    return matches;
}
