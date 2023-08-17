cmake_minimum_required(VERSION 3.5)

project(bst LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-std=c++11 -g -O2 -Wall -pedantic)

add_library(bst STATIC inc/bst.h)

target_include_directories(bst PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(bst PUBLIC ${PROJECT_COMPILE_DEFINITIONS})
set_target_properties(bst PROPERTIES LINKER_LANGUAGE CXX)

# Options
##################################################
option(BUILD_TESTS "Build tests." ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

install(TARGETS bst
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

