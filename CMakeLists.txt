cmake_minimum_required(VERSION 3.16)
project(dthread)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

include_directories("include")

add_executable(
    dthread-std
    "src/dthread-std.cpp"
)
