#pragma once

#include <memory>

class HandleCloser
{
public:
	void operator()(void* handle);
};

using HandleGuard = std::unique_ptr<void, HandleCloser>;
