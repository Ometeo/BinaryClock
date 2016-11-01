cmake_minimum_required(VERSION 2.8)
project(binaryClockProject)

# Add source code and setup folder structure.
set(main main.cpp)

# Add C++11 compiler flags.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-std=c++11 -stdlib=libc++ -O3 -Wall)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-std=c++11 -O3 -Wall)
endif()

# Create executable that links the source code, unit test, header file, and Boost.
add_executable(exe ${main})
