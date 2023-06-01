cmake_minimum_required(VERSION 3.10)
set(BIN max_stack)
project(${BIN} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(Threads)
if(Threads_FOUND)
    message ("Thread library was found")
else()
    message (FATAL_ERROR "Cannot find Threads package")
endif()

add_compile_options(-std=c++17 -g -O2 -Wall -pedantic)
add_library(maxstack inc/comprstack.h src/comprstack.cpp)
target_include_directories(maxstack PUBLIC inc)

enable_testing()
add_subdirectory(test)
