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

int lenght = sizeof ( int );
Arena fast ( 100 * lenght );
Arena fast2 ( fast );
static void Arena_Copy_Constructor ( benchmark::State &state )
{
  // Perform setup here
  for ( auto _ : state )
  {
    // This code gets timed
    int *p = ( int * ) fast.req ( lenght );
    *p = 5;

    int *q = ( int * ) fast2.req ( lenght );
    *q = 10;
  }
}

static void Arena ( benchmark::State &state )
{
  for ( auto _ : state )
  {
    // This code gets timed
    int *p = ( int * ) fast.req ( lenght );
    *p = 5;
  }
}

BENCHMARK ( Arena );
BENCHMARK ( Arena_Copy_Constructor );

// Run the benchmark
BENCHMARK_MAIN();
