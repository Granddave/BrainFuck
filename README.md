# Brainfuck

This repo contains

- a constexpr Brainfuck interpreter.
- a Brainfuck C transpiler.
- a Brainfuckception C transpiler.


## Build

```bash
$ mkdir build && cd build
$ cmake .. && make
```

## Constexpr interpreter

A class that takes a `constexpr std::string_view` and let's the user read a memory element with just
a few CPU instructions in runtime. I/O does not work for obvious reasons.


## Transpiler

```bash
$ build/brainfuck-c-transpiler/brainfuck-c-transpiler > main.c \
    && gcc -O3 main.c -o print-c-code \
    && ./print-c-code > main_2.c \
    && gcc -O3 main_2.c -o print-hw \
    && ./print-hw
```

## Brainfuckception (bfception)

A C++ program containing a brainfuck program which is transpiled to C code and printed.
This C program is compiled to an application that when run prints out the code for the original C++ file.

Not in a working state.
