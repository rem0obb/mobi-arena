cmake_minimum_required(VERSION 3.5)

set(OPTIMIZATIONS ON)

project(Arena-mobi VERSION 0.1)

find_package(benchmark REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "-lbenchmark  -lpthread")

if(OPTIMIZATIONS)
  set(CMAKE_CXX_FLAGS "-O2 -Os -fno-stack-protector -march=native -lbenchmark -lpthread")
endif()

add_library(Arena-mobi SHARED

        src/include/arena.cpp
        src/include/arena.hpp
        )

add_executable(TestBenchMark src/TestBenchMark.cpp )
target_link_libraries(TestBenchMark Arena-mobi)
