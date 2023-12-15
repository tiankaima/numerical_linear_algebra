//
// Created by tiankaima on 23-10-23.
//

#ifndef NUMERICAL_ALGEBRA_LU_FP_DECOMPOSITION_H
#define NUMERICAL_ALGEBRA_LU_FP_DECOMPOSITION_H

#include "CustomMath_lib.h"

typedef struct {
    Matrix L;
    Matrix U;
    Matrix P;
    Matrix Q;
} LU_FP_Decomposition_Result;

// LU Decomposition with Full Pivoting
void LU_FP_Decomposition(const Matrix &A, Matrix &L, Matrix &U, Matrix &P, Matrix &Q);

// LU Decomposition with Full Pivoting
LU_FP_Decomposition_Result LU_FP_Decomposition(const Matrix &A);

// Solve Ax = b using LU decomposition with Full Pivoting
Vector LU_FP_Solve(const Matrix &A, const Vector &b);

// LU Decomposition with Full Pivoting, and A is stored as L + U (ignoring L's all-one diagonal)
void LU_FP_Decomposition_InPlace(Matrix &A, Matrix &P, Matrix &Q);

// Solve Ax = b using LU decomposition with Full Pivoting, b is then replaced by x
void LU_FP_Solve_InPlace(Matrix &A, Vector &b);

#endif //NUMERICAL_ALGEBRA_LU_FP_DECOMPOSITION_H
