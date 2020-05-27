cmake_minimum_required(VERSION 3.16)
project(TraceGen)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")

include_directories(.)

add_subdirectory(lib)
# add_subdirectory(test)
