#pragma once

#include <vector>
#include <span>
#include <cstddef>

#include "Guards.h"

class Process {
public:
	explicit Process(HandleGuard&& process_handle);
	std::vector<std::byte> read(const void* address, size_t size) const;
	void write(void* address, std::span<const std::byte> data) const;
private:
	HandleGuard m_process_handle;
};
