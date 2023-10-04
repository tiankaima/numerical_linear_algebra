project(CustomMath)

set(HEADER_FILES
        Matrix.h
        Array.h
)

set(SOURCE_FILES
        Matrix.cpp
        Array.cpp
)

add_library(CustomMath_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})