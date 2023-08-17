# Testing
##################################################
find_package(Threads REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

set(TESTS ../main.cpp)
add_executable(main_test ${TESTS})
target_link_libraries(main_test
    PRIVATE
    GTest::GTest
    geometry
    pthread)
add_test(NAME main_test COMMAND main_test)
