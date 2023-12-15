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
        HouseholderMethod/HouseholderMethod.h
)

set(SOURCE_FILES
        Matrix/MatrixProperties.cpp
        Vector/Vector.cpp
        GaussMethod/TriangleMatrix.cpp
        GaussMethod/LU.cpp
        GaussMethod/LU_FP.cpp
        GaussMethod/LU_PP.cpp
        CholeskyMethod/Cholesky.cpp
        CholeskyMethod/Cholesky_LDLT.cpp
        InfinityNorm/InfinityNorm.cpp
        HouseholderMethod/HouseholderMethod.cpp
        IterationMethod/IterationMethod.h
        IterationMethod/IterationMethod.cpp
        PowerIteration/PowerIteration.cpp
        PowerIteration/PowerIteration.h
        HessenbergMethod/HessenbergMethod.cpp
        HessenbergMethod/HessenbergMethod.h
        QRMethod/DoubleShiftQRMethod.cpp
        QRMethod/DoubleShiftQRMethod.h
        QRMethod/QRMethod.cpp
        QRMethod/QRMethod.h
        CustomMath_lib.h
        base.h
        Matrix/MatrixGenerations.cpp
        Matrix/MatrixSubOperations.cpp
        Matrix/MatrixOperations.cpp
)

add_library(CustomMath_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})