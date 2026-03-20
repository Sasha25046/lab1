cmake_minimum_required(VERSION 3.10)
project(LexerLab)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(run_tests tests.cpp)
target_link_libraries(run_tests GTest::GTest GTest::gtest_main pthread)