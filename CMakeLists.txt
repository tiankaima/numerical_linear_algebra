cmake_minimum_required(VERSION 3.23)
project(numerical_algebra)
set(CMAKE_CXX_STANDARD 23)

# STATIC stuff (Windows)
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(BUILD_FOR_WIN TRUE)
endif ()
option(STATIC_BUILD "Build a static binary." ${BUILD_FOR_WIN})

if (STATIC_BUILD)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" CONFIG)
    set(BUILD_SHARED_LIBS OFF)
endif ()

OPTION(DEFINE_DEBUG "Define DEBUG macro" OFF)
if (DEFINE_DEBUG)
    add_definitions(-DDEBUG)
endif (DEFINE_DEBUG)

set(SOURCE_FILES main.cpp
        homeworks/homework_1.cpp
        homeworks/homework_1.h
        homeworks/homework_2.cpp
        homeworks/homework_2.h
        homeworks/homework_3.cpp
        homeworks/homework_3.h
        homeworks/homework_3_data.cpp
        homeworks/homework_3_data.h
        homeworks/homework_4.cpp
        homeworks/homework_4.h)
add_executable(numerical_algebra ${SOURCE_FILES})
include_directories(CustomMath_lib)
target_link_libraries(numerical_algebra CustomMath_lib)

add_subdirectory(CustomMath_lib)
add_subdirectory(Doctest_tests)
