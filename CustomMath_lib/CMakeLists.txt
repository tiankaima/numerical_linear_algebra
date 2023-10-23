project(CustomMath)

set(HEADER_FILES
        Matrix/Matrix.h
        Vector/Vector.h
        CholeskyMethod/CholeskyMethod.h
        GaussMethod/TriangleMatrix.h
        GaussMethod/LU.h
        GaussMethod/LU_FP.h
        GaussMethod/LU_PP.h
)

set(SOURCE_FILES
        Matrix/Matrix.cpp
        Vector/Vector.cpp
        CholeskyMethod/CholeskyMethod.cpp
        GaussMethod/TriangleMatrix.cpp
        GaussMethod/LU.cpp
        GaussMethod/LU_FP.cpp
        GaussMethod/LU_PP.cpp
)

add_library(CustomMath_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})