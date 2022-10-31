cmake_minimum_required(VERSION 3.10.2)

project(constexpr-brainfuck LANGUAGES CXX)
add_executable(constexpr-brainfuck
    ${CMAKE_CURRENT_SOURCE_DIR}/constexpr-brainfuck.h
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
target_compile_options(constexpr-brainfuck PRIVATE -Wall -Wextra -Wpedantic -Werror)
set_target_properties(constexpr-brainfuck PROPERTIES CXX_STANDARD 20)
