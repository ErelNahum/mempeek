cmake_minimum_required(VERSION 3.15)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(_core MODULE
    src/Bindings.cpp
    src/WinApi.cpp
    src/Guards.cpp
    src/Exceptions.cpp
    src/Process.cpp
    src/MemoryRegion.cpp
)

install(TARGETS _core DESTINATION ${SKBUILD_PROJECT_NAME})
