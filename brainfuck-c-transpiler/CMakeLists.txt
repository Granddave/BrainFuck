cmake_minimum_required(VERSION 3.10.2)

project(brainfuck-c-transpiler LANGUAGES CXX)
add_executable(brainfuck-c-transpiler
    ${CMAKE_CURRENT_SOURCE_DIR}/brainfuck-c-transpiler.h
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
target_compile_options(brainfuck-c-transpiler PRIVATE -Wall -Wextra -Wpedantic -Werror)
set_target_properties(brainfuck-c-transpiler PROPERTIES CXX_STANDARD 20)
