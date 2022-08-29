cmake_minimum_required(VERSION 3.5)

project(thr03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(thr03 main.cpp cmutex.h)
