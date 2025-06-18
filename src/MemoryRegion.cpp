#include "MemoryRegion.h"

MemoryRegion::MemoryRegion(const MEMORY_BASIC_INFORMATION &information)
    : m_base_address{reinterpret_cast<std::uintptr_t>(information.BaseAddress)},
      m_size{information.RegionSize},
      m_state{information.State},
      m_type{information.Type},
      m_protection_flags{information.Protect} {}

std::uintptr_t MemoryRegion::base_address() const
{
    return m_base_address;
}

size_t MemoryRegion::size() const
{
    return m_size;
}

MemoryRegionState MemoryRegion::state() const
{
    return m_state;
}

MemoryRegionType MemoryRegion::type() const
{
    return m_type;
}

uint32_t MemoryRegion::protection_flags() const
{
    return m_protection_flags;
}
