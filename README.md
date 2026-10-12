# Mandelbrot Set Thread Pool Renderer

A high-performance fractal rendering engine built entirely in C++. This project demonstrates the practical application of concurrent programming (multithreading) and complex mathematics to generate high-resolution representations of the Mandelbrot Set.

## Project Overview

The goal of this project is to explore CPU-level parallelism. Instead of processing pixels sequentially or relying on heavy external libraries, the renderer implements a custom **Thread Pool** architecture using the C++ Standard Library (`<thread>`, `<mutex>`, `<condition_variable>`). 

## Project Structure

```text
Mandelbrot-Project/
│
├── README.md
├── images/
    └── example.png
└── src/
    ├── main.cpp
    ├── mandelbrot.cpp
    ├── mandelbrot.h
    ├── threadpool.cpp
    └── threadpool.h
```

- `threadpool` defines the class `ThreadPool`, which contains the basic structure to distribute the tasks among the different threads. 
- `mandelbrot` contains the two algorithms to process pixels, one using the `ThreadPool` class and the other one using a classic iterative approach.
- `main` runs the two different methods and computes the duration of each one to compare the architectures.

## Mathematical Background

Let $`ℂ`$ be the complex plane, and let $`\{z_n\}_{n}`$ be a sequence in $`ℂ`$ defined by

```math
z_{n+1} = z_n^2 + c
```
where $`z_0 = 0`$ and $`c \in ℂ`$. The set of complex numbers $`c`$ such that $`\{z_n\}`$ does not diverge is called the Mandelbrot set. It can be proved that if at some point, there exists a $z$ such that $`\mid z \mid > 2`$, then the sequence will diverge. Computationally, we can choose a number of iterations to define the _infinity_ (say `N = 1000`); if after those iterations the sequence does not escape, we paint it as black. If it does escape, we color it depending on the iteration number it broke the condition. Notice that we are using the condition `norm(z) < 16` instead of `4` to achieve a smooth image rendering. 

The importance of the project relies on how we are rendering the colors of each pixel: thanks to the `ThreadPool` class, we can compute all the rows simultaneously instead of waiting for the previous row to complete the operations. This approach makes the algorithm highly efficient compared to the traditional method. 

Anyways, the result of both of them is a smooth image representing the fractal of the Mandelbrot set, a beautiful mathematical object that shows us, once more, the strong connections between mathematics and informatics.

## How to Compile and Run

This project requires zero external libraries. You only need a C++ compiler (GCC/Clang) that supports C++11 or higher.

**1. Compilation:**
To achieve maximum performance, it is recommended to enable compiler optimizations (`-O3`) and link the POSIX thread library (`-pthread`).

```bash
g++ src/main.cpp src/mandelbrot.cpp src/threadpool.cpp -o mandelbrot -O3 -pthread
```

**2. Execution:**

```bash
./mandelbrot
```

It will print out two different execution times, one corresponding to running the algorithm with threading and the other one without it.

## Conclusion

A very simple system was used to test this program:
- CPU: Intel(R) N100, 4 threads
- RAM: 12 GB
- OS: Ubuntu 22.04 LTS, x64

The results were astonishing. In an `800 x 800` pixel grid with `N=1000` iterations, it took around `160 ms` with threading and `400 ms` with no threading. This is approximately `2.5` times faster. Changing the pixel grid to `8000 x 8000` and keeping the same number of iterations, it can be seen the real power of threading. It took about `32 s` with threading and more than `100 s` without it. This means threading speeds up the algorithm more than `3` times! Notice that in both cases `64,000,000` computations are being made; the difference is how tasks are assigned: while the second method (no threading) runs the code line by line, waiting for each computation, the first one (threading) runs the whole code and implements a queue where the tasks (computing rows) are posted. Each time a thread is free, it takes a task and starts working in parallel with the other ones.
