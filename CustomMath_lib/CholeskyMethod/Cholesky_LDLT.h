//
// Created by tiankaima on 23-10-23.
//

#ifndef NUMERICAL_ALGEBRA_CHOLESKY_LDLT_H
#define NUMERICAL_ALGEBRA_CHOLESKY_LDLT_H

#include "CustomMath_lib.h"

typedef struct {
    Matrix L;
    Matrix D;
} Cholesky_LDLT_Result;

/// Decomposition A = LDL^T, L is lower triangular, det(L) == 1, D is diagonal
Cholesky_LDLT_Result Cholesky_LDLT_Decomposition(const Matrix &A);

/// Solve Ax = b using Cholesky decomposition
Vector Cholesky_LDLT_Solve(const Matrix &A, const Vector &b);

/// Decomposition A = LDL^T, L is lower triangular, D is diagonal, and L and D are directly stored in A
void Cholesky_LDLT_Decomposition_InPlace(Matrix &A);

/// Solve Ax = b using Cholesky decomposition, b is then replaced by x
void Cholesky_LDLT_Solve_InPlace(Matrix &A, Vector &b);

#endif //NUMERICAL_ALGEBRA_CHOLESKY_LDLT_H
