// ------------------------------------------------------------------
// Test BenchMark Arena-mobi
// ------------------------------------------------------------------


#include "include/arena.hpp"

#include <iostream>
#include <chrono>
#include <benchmark/benchmark.h>

Arena fast ( 1 * sizeof ( int ) );

// ------------------------------------------------------------------
// Stack
// ------------------------------------------------------------------
static void Stack ( benchmark::State &state )
{
  // Perform setup here
  for ( auto _ : state )
  {
    // This code gets timed
    int p = 5;
  }
}

BENCHMARK ( Stack );


// ------------------------------------------------------------------
// Heap
// ------------------------------------------------------------------

static void Heap ( benchmark::State &state )
{
  // Perform setup here
  for ( auto _ : state )
  {
    // This code gets timed
    int *p = new int;
    *p = 5;
    delete p;
  }
}

BENCHMARK ( Heap );

// ------------------------------------------------------------------
// Arena
// ------------------------------------------------------------------

static void Arena ( benchmark::State &state )
{
  // Perform setup here
  for ( auto _ : state )
  {
    // This code gets timed
    int *p = ( int * ) fast.req ( sizeof ( int ) );
    *p = 5;
    fast.dell();
  }
}

BENCHMARK ( Arena );




// Run the benchmark
BENCHMARK_MAIN();
