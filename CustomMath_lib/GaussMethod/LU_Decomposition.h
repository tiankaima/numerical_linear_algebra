//
// Created by tiankaima on 23-10-23.
//

#ifndef NUMERICAL_ALGEBRA_LU_DECOMPOSITION_H
#define NUMERICAL_ALGEBRA_LU_DECOMPOSITION_H

#include "CustomMath_lib.h"

typedef struct {
    Matrix L;
    Matrix U;
} LU_Decomposition_Result;

/// Decomposition A = LU, det(L) == 1
void LU_Decomposition(const Matrix &A, Matrix &L, Matrix &U);

/// Decomposition A = LU, det(L) == 1
LU_Decomposition_Result LU_Decomposition(const Matrix &A);

/// Solve Ax = b using LU decomposition
Vector LU_Solve(const Matrix &A, const Vector &b);

/// Decomposition A = LU, det(L) == 1, and A is stored as L + U (ignoring L's all-one diagonal)
void LU_Decomposition_InPlace(Matrix &A);

/// Solve Ax = b using LU decomposition, b is then replaced by x
void LU_Solve_InPlace(Matrix &A, Vector &b);

#endif //NUMERICAL_ALGEBRA_LU_DECOMPOSITION_H
