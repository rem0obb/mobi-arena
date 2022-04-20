#include "include/arena.hpp"
#include <iostream>
#include "include/arena.hpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

const int Max = 1000000;
Arena fast(Max*sizeof(int));

void stack()
{
    int a = 5;
}

void heap()
{
    int * p = new int;
    *p = 5;
    delete p;
}

void arena()
{
    int * p = (int*) fast.req(sizeof(int));
    *p = 5;
}

int main()
{
    // ------------------------------------------------------------------
    // Stack
    // ------------------------------------------------------------------

    auto start = high_resolution_clock::now();
    for (int i = 0; i < Max; ++i)
        stack();
    auto end = high_resolution_clock::now();

    cout << "Stack: ";
    cout.width(4);
    cout << right;
    cout << duration_cast<milliseconds>(end - start).count() << " milissegundos" << endl;

    // ------------------------------------------------------------------
    // Heap
    // ------------------------------------------------------------------

    start = high_resolution_clock::now();
    for (int i = 0; i < Max; ++i)
        heap();
    end = high_resolution_clock::now();

    cout << "Heap:  ";
    cout.width(4);
    cout << right;
    cout << duration_cast<milliseconds>(end - start).count() << " milissegundos" << endl;

    // ------------------------------------------------------------------
    // Arena
    // ------------------------------------------------------------------

    start = high_resolution_clock::now();
    for (int i = 0; i < Max; ++i)
        arena();
    end = high_resolution_clock::now();

    cout << "Arena: ";
    cout.width(4);
    cout << right;
    cout << duration_cast<milliseconds>(end - start).count() << " milissegundos" << endl;
}
