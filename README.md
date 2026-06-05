# Some Implemented Algorithms

Collection of standalone C implementations of classic algorithms and data structures, kept as small runnable examples.

## Purpose and target
- Purpose: Reference implementations and practice exercises.
- Target: Learning, quick testing, and interview prep.

## Requirements
- C compiler (GCC, Clang, or MSVC).
- Windows/macOS/Linux.

## What's inside
- algorithms/
  - sorting/: QuickSort.c, MergeSort.c, InsertionSort.c
  - data-structures/: Singly_LinkedList.c, Doubly_LinkedList.c, MinHeap_array_based.c, MinHeap_tree_based.c, Queue.h
  - math/: factorial.c, fib.c, GCD.c, num_to_base.c, matrix_solver.c
  - dynamic-programming/: kadane.c
  - cryptography/: RES_Cryptography.c, RES_Cryptography2.c
- puzzles/
  - sudoku/: sudoku_solver.c, sudoku.txt

## Build and run (example)
```bash
cd algorithms/sorting
gcc QuickSort.c -o QuickSort
./QuickSort
```


## Naming and layout
- One algorithm per file, minimal dependencies.
- Headers are kept alongside their data structure implementations.
