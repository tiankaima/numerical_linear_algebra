//
// Created by tiankaima on 23-10-24.
//

#ifndef NUMERICAL_ALGEBRA_INFINITYNORM_H
#define NUMERICAL_ALGEBRA_INFINITYNORM_H

#include "Vector/Vector.h"
#include "Matrix/Matrix.h"
#include "GaussMethod/GaussMethod.h"
#include "CholeskyMethod/CholeskyMethod.h"

lld InfinityNorm(const Matrix &A);

lld InfinityNorm(const Vector &x);

Vector sign(const Vector &vector);

lld InfinityNormApprox(const Matrix &A);

#endif //NUMERICAL_ALGEBRA_INFINITYNORM_H
