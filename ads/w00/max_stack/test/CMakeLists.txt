include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(main_test tests.h main.cpp)

target_link_libraries(main_test
 PRIVATE
  GTest::GTest
  maxstack)

add_test(multiply_gtests main_test)
