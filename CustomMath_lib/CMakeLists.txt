project(CustomMath)

set(HEADER_FILES
        Matrix.h
        Array.h
        GaussMethod.cpp
        GaussMethod.h
        CholeskyMethod.cpp
        CholeskyMethod.h
)

set(SOURCE_FILES
        Matrix.cpp
        Array.cpp
        GaussMethod.cpp
        GaussMethod.h
        CholeskyMethod.cpp
        CholeskyMethod.h
)

add_library(CustomMath_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})