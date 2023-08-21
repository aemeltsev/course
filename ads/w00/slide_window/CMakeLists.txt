cmake_minimum_required(VERSION 2.6)

set(BIN slide_window)
project(${BIN} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-std=c++11 -g -O2 -Wall -pedantic)

set(SOURCES inc/comprstack.h main.cpp)

add_executable(${BIN} ${SOURCES})

install(TARGETS ${BIN}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
