# Mandelbrot Set Thread Pool Renderer

A high-performance fractal rendering engine built entirely in C++. This project demonstrates the practical application of concurrent programming (multithreading) and complex mathematics to generate high-resolution representations of the Mandelbrot Set.

## Project Overview

The goal of this project is to explore CPU-level parallelism. Instead of processing pixels sequentially or relying on heavy external libraries, the renderer implements a custom **Thread Pool** architecture using the C++ Standard Library (`<thread>`, `<mutex>`, `<condition_variable>`). 

## Key Features

## Concurrent Architecture

## How to Compile and Run

This project requires zero external libraries. You only need a C++ compiler (GCC/Clang) that supports C++11 or higher.

**1. Compilation:**
To achieve maximum mathematical performance, it is recommended to enable compiler optimizations (`-O3`) and link the POSIX thread library (`-pthread`).

```bash
g++ src/main.cpp src/threadpool.cpp -o mandelbrot -O3 -pthread
```

**2. Execution:**

```bash
./mandelbrot
