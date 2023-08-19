cmake_minimum_required(VERSION 3.5)

project(dlist LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-std=c++17 -g -O2 -Wall )#-pedantic)

add_executable(dlist list.h test.cpp)

install(TARGETS dlist
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
