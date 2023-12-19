//
// Created by tiankaima on 23-10-23.
//

#ifndef NUMERICAL_ALGEBRA_LU_PP_DECOMPOSITION_H
#define NUMERICAL_ALGEBRA_LU_PP_DECOMPOSITION_H

#include "CustomMath_lib.h"

typedef struct {
    Matrix L;
    Matrix U;
    Matrix P;
} LU_PP_Decomposition_Result;

// LU Decomposition with Partial Pivoting
LU_PP_Decomposition_Result LU_PP_Decomposition(const Matrix &A);

// Solve Ax = b using LU decomposition with Partial Pivoting
Vector LU_PP_Solve(const Matrix &A, const Vector &b);

// LU Decomposition with Partial Pivoting, and A is stored as L + U (ignoring L's all-one diagonal)
Matrix LU_PP_Decomposition_InPlace(Matrix &A);

// Solve Ax = b using LU decomposition with Partial Pivoting, b is then replaced by x
void LU_PP_Solve_InPlace(Matrix &A, Vector &b);

#endif //NUMERICAL_ALGEBRA_LU_PP_DECOMPOSITION_H
