cmake_minimum_required(VERSION 3.10)
set(BIN net_queue)
project(${BIN} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads)
if(Threads_FOUND)
    message ("Thread library was found")
else()
    message (FATAL_ERROR "Cannot find Threads package")
endif()

option(USE_TEST "Enable Tests" ON)

if(USE_TEST)
    add_compile_options(-std=c++11 -g -O2 -Wall -pedantic)
    add_library(netqueue inc/nqueue.h src/nqueue.cpp)
    target_include_directories(netqueue PUBLIC inc)

    enable_testing()
    add_subdirectory(test)

else()
    include_directories(inc src test)
    add_compile_options(-std=c++11 -g -O2 -Wall -Werror -pedantic)
    add_executable(netqueue inc/nqueue.h src/nqueue.cpp src/main.cpp)

endif()
