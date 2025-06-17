#include "Guards.h"

#include <Windows.h>

void HandleCloser::operator()(void* const handle)
{
	try {
		CloseHandle(handle);
	} catch(...) {}
}
