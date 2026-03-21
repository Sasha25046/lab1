cmake_minimum_required(VERSION 3.10)
project(LexerLab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(COVERAGE "Enable coverage reporting" ON)

if(COVERAGE)
    message("Coverage enabled")
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -static-libgcc")

find_package(GTest REQUIRED)

add_executable(run_tests tests.cpp)

target_include_directories(run_tests PRIVATE ${GTEST_INCLUDE_DIRS})

target_link_libraries(run_tests 
    GTest::gtest 
    GTest::gtest_main 
    pthread
)