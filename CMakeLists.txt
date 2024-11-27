cmake_minimum_required(VERSION 3.0)

project(BigIntProject)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Werror -pedantic -lm)

add_executable(out main.cpp class.cpp)