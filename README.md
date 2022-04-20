# Arena-mobi

Arena created for project mobi-av disponibilized in github to usage

# Benchmark

Benchmark using [benchmark-google](https://github.com/google/benchmark) 

![BenchMark](assets/Arena-BenchMark.png)

for compile benchmark 
```
  mkdir build
  cd build
  cmake ..
  make

```

# Usage Arena

```C
  #include "include/arena.hpp"
  
  Arena fast(3*sizeof(int)); // allocate 3 blocks long from an length int
  
  // requests blocks
  int *p1 = (int*)fast.req(sizeof(int));
  *p1 = 100;
  
  int *p2 = (int*)fast.req(sizeof(int));
  *p2 = 400;
  
  int *p3 = (int*)fast.req(sizeof(int));
  *p3 = 400;
```
