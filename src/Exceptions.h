#include <system_error>

class WindowsException : public std::system_error
{
public:
    WindowsException(uint32_t error_code);
};

#define THROW_WINDOWS_EXCEPTION() throw WindowsException(GetLastError())
