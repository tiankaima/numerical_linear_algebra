cmake_minimum_required(VERSION 3.26)
project(numerical_algebra)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES main.cpp)
add_executable(numerical_algebra ${SOURCE_FILES})

include_directories(CustomMath_lib)
add_subdirectory(CustomMath_lib)

target_link_libraries(numerical_algebra CustomMath_lib)

add_subdirectory(Doctest_tests)