# 🚀 Some Implemented Algorithms

![Language](https://img.shields.io/badge/language-C-blue.svg)

A collection of standalone C implementations of classic algorithms, data structures, and puzzles. These are kept as small, runnable examples designed for clarity and efficiency.

## 🎯 Purpose and Target

- **Purpose**: Reference implementations, practice exercises, and exploring optimizations.
- **Target**: Learning, quick testing, and technical interview preparation.

## ⚙️ Requirements

- **C Compiler**: GCC, Clang, or MSVC.
- **OS**: Windows, macOS, or Linux.

## 📂 What's Inside

### 🧠 Algorithms

* **Sorting** (`algorithms/sorting/`)
  * `QuickSort.c`, `MergeSort.c`, `InsertionSort.c`
* **Data Structures** (`algorithms/data-structures/`)
  * `Singly_LinkedList.c`, `Doubly_LinkedList.c`
  * `MinHeap_array_based.c`, `MinHeap_tree_based.c`
  * `Queue.h`
* **Math** (`algorithms/math/`)
  * `binomial.c` — *(Binomial coefficient implementation)*
  * `factorial.c`, `fib.c`, `GCD.c`
  * `num_to_base.c`, `matrix_solver.c`
* **Dynamic Programming** (`algorithms/dynamic-programming/`)
  * `kadane.c`
* **Cryptography** (`algorithms/cryptography/`)
  * `RES_Cryptography.c`, `RES_Cryptography2.c`

### 🧩 Puzzles

* **Sudoku** (`puzzles/sudoku/`)
  * `sudoku_solver.c`
  * `sudoku.txt`

## 🚀 Build and Run (Example)

```bash
# Navigate to the target directory
cd algorithms/sorting

# Compile the C file
gcc QuickSort.c -o QuickSort

# Run the executable
./QuickSort
```

## 📐 Naming and Layout

- **Simplicity**: One algorithm per file with minimal dependencies.
- **Organization**: Headers are kept alongside their corresponding data structure implementations.
