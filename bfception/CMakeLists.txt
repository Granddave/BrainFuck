cmake_minimum_required(VERSION 3.10.2)

project(bfception LANGUAGES CXX)
add_executable(bfception
    ${CMAKE_CURRENT_SOURCE_DIR}/step_2_main.cpp
)
target_compile_options(bfception PRIVATE -Wall -Wextra -Wpedantic -Werror)
set_target_properties(bfception PROPERTIES CXX_STANDARD 20)
