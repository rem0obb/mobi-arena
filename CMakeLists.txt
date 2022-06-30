cmake_minimum_required(VERSION 3.5)
project(Arena VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(OPTIMIZATIONS ON)

# find package
find_package(benchmark REQUIRED)

set(CMAKE_CXX_FLAGS "")
if(OPTIMIZATIONS)
  set(CMAKE_CXX_FLAGS "-O2 -Os -fno-stack-protector -march=native")
endif()

add_library(Arena SHARED

  src/include/arena.cpp
  src/include/arena.hpp

)

# add executable benchmark
include(GoogleTest)
add_executable(arena_benchmark benchmark/benchmark.cpp)
target_link_libraries(arena_benchmark benchmark::benchmark Arena)

# add executable gtest
add_definitions(-DUNIT_TESTS)
add_executable(arena_test test/test.cpp)
target_link_libraries(arena_test gtest gtest_main Arena)