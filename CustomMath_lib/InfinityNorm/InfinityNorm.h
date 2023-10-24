//
// Created by tiankaima on 23-10-24.
//

#ifndef NUMERICAL_ALGEBRA_INFINITYNORM_H
#define NUMERICAL_ALGEBRA_INFINITYNORM_H

#include "Vector/Vector.h"
#include "Matrix/Matrix.h"
#include "GaussMethod/GaussMethod.h"
#include "CholeskyMethod/CholeskyMethod.h"

lld MatrixNorm_Infinity(const Matrix &A);

lld VectorNorm_Infinity(const Vector &x);

Vector sign(const Vector &vector);

lld MatrixNorm_1(const Matrix &A);

#endif //NUMERICAL_ALGEBRA_INFINITYNORM_H
