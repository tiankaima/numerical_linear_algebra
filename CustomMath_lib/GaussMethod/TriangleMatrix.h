//
// Created by tiankaima on 23-10-23.
//

#ifndef NUMERICAL_ALGEBRA_TRIANGLEMATRIX_H
#define NUMERICAL_ALGEBRA_TRIANGLEMATRIX_H

#include "CustomMath_lib.h"

/// Solve Lx = b and return x
Vector LowerTriangleMatrix_Solve(const Matrix &L, const Vector &b, bool isDiagonalUnit = false);

/// Solve Ux = b and return x
Vector UpperTriangleMatrix_Solve(const Matrix &U, const Vector &b, bool isDiagonalUnit = false);

/// Solve Lx = b, b is then replaced by x
void LowerTriangleMatrix_Solve_InPlace(const Matrix &L, Vector &b, bool isDiagonalUnit = false);

/// Solve Ux = b, b is then replaced by x
void UpperTriangleMatrix_Solve_InPlace(const Matrix &U, Vector &b, bool isDiagonalUnit = false);

#endif //NUMERICAL_ALGEBRA_TRIANGLEMATRIX_H
