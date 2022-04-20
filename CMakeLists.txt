cmake_minimum_required(VERSION 3.5)

project(Arena-mobi VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(Arena-mobi SHARED

        src/include/arena.cpp
        src/include/arena.hpp
        )

add_executable(TestBenchMark src/TestBenchMark.cpp )
target_link_libraries(TestBenchMark Arena-mobi)
