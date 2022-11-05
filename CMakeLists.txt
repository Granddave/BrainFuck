cmake_minimum_required(VERSION 3.10.2)

project(brainfuck LANGUAGES CXX)

add_subdirectory(constexpr-brainfuck)
add_subdirectory(brainfuck-c-transpiler)
add_subdirectory(bfception)
