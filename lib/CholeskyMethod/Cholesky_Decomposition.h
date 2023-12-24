//
// Created by tiankaima on 23-10-23.
//

#ifndef NUMERICAL_ALGEBRA_CHOLESKY_DECOMPOSITION_H
#define NUMERICAL_ALGEBRA_CHOLESKY_DECOMPOSITION_H

#include "../../includes/NLAMethods.h"

/// Decomposition A = LL^T, L is lower triangular
Matrix Cholesky_Decomposition(const Matrix &A);

/// Solve Ax = b using Cholesky decomposition
Vector Cholesky_Solve(const Matrix &A, const Vector &b);

/// Decomposition A = LL^T, L is lower triangular, and L is directly stored in A
void Cholesky_Decomposition_InPlace(Matrix &A);

/// Solve Ax = b using Cholesky decomposition, b is then replaced by x
void Cholesky_Solve_InPlace(Matrix &A, Vector &b);

#endif //NUMERICAL_ALGEBRA_CHOLESKY_DECOMPOSITION_H
