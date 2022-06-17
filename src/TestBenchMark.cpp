// ------------------------------------------------------------------
// Test BenchMark Arena-mobi
// ------------------------------------------------------------------


#include "include/arena.hpp"
#include <benchmark/benchmark.h>

// ------------------------------------------------------------------
// Stack
// ------------------------------------------------------------------
static void Stack ( benchmark::State &state )
{
  // Perform setup here
  for ( auto _ : state )
  {
    // This code gets timed
    volatile int p = 5;
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
    volatile int *p = new int;
    *p = 5;
    delete p;
  }
}

BENCHMARK ( Heap );

// ------------------------------------------------------------------
// Arena
// ------------------------------------------------------------------

int lenght = sizeof ( int );
Arena fast ( 100 * lenght );
static void Arena_Copy_Constructor ( benchmark::State &state )
{
  // Perform setup here
  for ( auto _ : state )
  {
    // This code gets timed
    int *p = static_cast<int*>(fast.req ( lenght ));
    *p = 5;

  }
}

Arena fast2 ( 100 * lenght );
static void Arena ( benchmark::State &state )
{
  for ( auto _ : state )
  {
    // This code gets timed
    int *p = static_cast<int*>(fast2.req ( lenght ));
    *p = 5;
  }
}

BENCHMARK ( Arena );
BENCHMARK ( Arena_Copy_Constructor );

// Run the benchmark
BENCHMARK_MAIN();
