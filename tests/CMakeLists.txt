cmake_minimum_required(VERSION 3.17)
project(templateArrayTests)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/master.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        tests
        test.cc
)
target_link_libraries(
        tests
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
