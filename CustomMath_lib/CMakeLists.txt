project(CustomMath)

set(HEADER_FILES
        Matrix/Matrix.h
        Vector/Vector.h
        GaussMethod/TriangleMatrix.h
        GaussMethod/LU_Decomposition.h
        GaussMethod/LU_FP_Decomposition.h
        GaussMethod/LU_PP_Decomposition.h
        CholeskyMethod/CholeskyMethod.h
        GaussMethod/GaussMethod.h
        CholeskyMethod/Cholesky_Decomposition.h
        CholeskyMethod/Cholesky_LDLT.h
        InfinityNorm/InfinityNorm.h
        HouseholderMethod/HouseholderMethod.h
)

set(SOURCE_FILES
        Matrix/MatrixProperties.cpp
        Vector/Vector.cpp
        GaussMethod/TriangleMatrix.cpp
        GaussMethod/LU_Decomposition.cpp
        GaussMethod/LU_FP_Decomposition.cpp
        GaussMethod/LU_PP_Decomposition.cpp
        CholeskyMethod/Cholesky_Decomposition.cpp
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
        JacobiMethod/JacobiMethod.cpp
        JacobiMethod/JacobiMethod.h
)

add_library(CustomMath_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})