cmake_minimum_required(VERSION 3.26)
project(numerical_algebra)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES main.cpp
        homeworks/homework_1.cpp
        homeworks/homework_1.h)
add_executable(numerical_algebra ${SOURCE_FILES})

include_directories(CustomMath_lib)
add_subdirectory(CustomMath_lib)

target_link_libraries(numerical_algebra CustomMath_lib)

add_subdirectory(Doctest_tests)

# STATIC stuff (Windows)
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(BUILD_FOR_WIN TRUE)
endif()
option(STATIC_BUILD "Build a static binary." ${BUILD_FOR_WIN})

if (STATIC_BUILD)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" CONFIG)
    set(BUILD_SHARED_LIBS OFF)
endif()