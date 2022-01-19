cmake_minimum_required(VERSION 3.5)

project(check_brackets LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-std=c++11 -g -O2 -Wall -Wextra -pedantic)

add_executable(check_brackets main.cpp)
