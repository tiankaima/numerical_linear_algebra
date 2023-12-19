//
// Created by tiankaima on 23-10-24.
//

#ifndef NUMERICAL_ALGEBRA_INFINITYNORM_H
#define NUMERICAL_ALGEBRA_INFINITYNORM_H

#include "CustomMath_lib.h"

/// Calculate infinity norm of a matrix
lld MatrixNorm_Infinity(const Matrix &A);

/// Calculate E(A) which is the non-diagonal norm of A
lld MatrixNorm_E(const Matrix &A);

/// Calculate infinity norm of a vector
lld VectorNorm_Infinity(const Vector &x);

/// Estimate 1 norm of a matrix
lld MatrixNorm_1(const Matrix &B);

/// Estimate 1 norm of A^(-T)
lld MatrixNorm_A_Inv_T_1(const Matrix &A);

#endif //NUMERICAL_ALGEBRA_INFINITYNORM_H
