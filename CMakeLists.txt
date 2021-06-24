cmake_minimum_required(VERSION 3.10.2)

project(brainfuck LANGUAGES CXX)
add_executable(
  brainfuck
  ${CMAKE_CURRENT_SOURCE_DIR}/brainfuck/brainfuck.h
  ${CMAKE_CURRENT_SOURCE_DIR}/brainfuck/brainfuck.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/brainfuck/main.cpp)
target_compile_options(brainfuck PRIVATE -Wall -Wextra -Wpedantic -Werror)
set_target_properties(brainfuck PROPERTIES CXX_STANDARD 20)
