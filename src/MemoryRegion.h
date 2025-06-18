#pragma once

#include <cstdint>

#include <Windows.h>

enum class MemoryRegionState : uint32_t
{
    FREE = MEM_FREE,
    RESERVED = MEM_RESERVE,
    COMMITED = MEM_COMMIT,
};

enum class MemoryRegionType : uint32_t
{
    PRIVATE = MEM_PRIVATE,
    MAPPED = MEM_MAPPED,
    IMAGE = MEM_IMAGE,
    UNDEFINED = NULL,
};

class MemoryRegion
{
public:
    explicit MemoryRegion(const MEMORY_BASIC_INFORMATION& information);
    std::uintptr_t base_address() const;
    size_t size() const;
    MemoryRegionState state() const;
    MemoryRegionType type() const;
    uint32_t protection_flags() const;
private:
    std::uintptr_t m_base_address;
    size_t m_size;
    MemoryRegionState m_state;
    MemoryRegionType m_type;
    uint32_t m_protection_flags;
};
