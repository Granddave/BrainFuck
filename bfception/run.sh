#!/bin/bash

set -e
set -x
cd "$(dirname "$0")"

echo "Step 1: Generate step_2_main.cpp"
time ./generate_brainfuck_code.py
echo "Step 2: Building generated code"
mkdir -p build
pushd build
cmake ..
time make
popd
echo "Transpiling brainfuck to C"
build/bfception > step_3_generated.c
echo "Compiling generated transpiled C code"
time gcc -O3 step_3_generated.c -o build/step_4_bfception
echo "Generating C++ code from transpiled C code"
build/step_4_bfception > step_5_main.cpp
echo "done"
