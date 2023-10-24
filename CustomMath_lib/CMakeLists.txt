project(CustomMath)

set(HEADER_FILES
        Matrix/Matrix.h
        Vector/Vector.h
        GaussMethod/TriangleMatrix.h
        GaussMethod/LU.h
        GaussMethod/LU_FP.h
        GaussMethod/LU_PP.h
        CholeskyMethod/CholeskyMethod.h
        GaussMethod/GaussMethod.h
        CholeskyMethod/Cholesky.h
        CholeskyMethod/Cholesky_LDLT.h
        InfinityNorm/InfinityNorm.h
)

set(SOURCE_FILES
        Matrix/Matrix.cpp
        Vector/Vector.cpp
        GaussMethod/TriangleMatrix.cpp
        GaussMethod/LU.cpp
        GaussMethod/LU_FP.cpp
        GaussMethod/LU_PP.cpp
        CholeskyMethod/Cholesky.cpp
        CholeskyMethod/Cholesky_LDLT.cpp
        InfinityNorm/InfinityNorm.cpp
)

add_library(CustomMath_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})