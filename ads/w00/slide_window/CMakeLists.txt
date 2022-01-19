cmake_minimum_required(VERSION 2.6)
set(BIN slide_window)
project(${BIN} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include_directories(inc src test)

find_package(Threads)

if(Threads_FOUND)
    message ("Thread library was found")
else()
    message (FATAL_ERROR "Cannot find Threads package")
endif()

find_package(GTest)

if(GTest_FOUND)
    message("Google Test library was found")
else()
    message(FATAL_ERROR "Cannot find Google Test package")
endif()

add_compile_options(-std=c++11 -g -O2 -Wall)
link_libraries(pthread)
link_libraries(gtest)

set(HEADERS comprstack.h tests.h)
set(SOURCES main.cpp)
set(REQUIRED_LIBRARIES pthread gtest)

add_executable(${BIN} ${SOURCES})
target_link_libraries(${BIN} PRIVATE ${EXTRA_LIBS} ${REQUIRED_LIBRARIES})

