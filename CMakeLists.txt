project(controller
    DESCRIPTION "linux shared memory test"
    LANGUAGES C CXX)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(shared_memory_manager)
add_subdirectory(master)
add_subdirectory(slave)
