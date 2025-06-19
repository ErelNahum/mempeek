#include "Exceptions.h"


WindowsException::WindowsException(const uint32_t error_code)
    : std::system_error{std::error_code(error_code, std::system_category())} {}
