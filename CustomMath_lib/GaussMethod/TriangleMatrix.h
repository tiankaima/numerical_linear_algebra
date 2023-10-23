//
// Created by tiankaima on 23-10-23.
//

#ifndef NUMERICAL_ALGEBRA_TRIANGLEMATRIX_H
#define NUMERICAL_ALGEBRA_TRIANGLEMATRIX_H

#include "iostream"
#include "vector"
#include "Vector/Vector.h"
#include "Matrix/Matrix.h"

/*
 * Solve Lx = b
 * TIME: O(n^2)
 *
 * @param L: a lower triangular matrix
 */
Vector LowerTriangleMatrixSolve(const Matrix &L, const Vector &b, bool isDiagonalUnit = false);

/*
 * Solve Ux = b, where U is an upper triangular matrix
 * TIME: O(n^2)
 *
 * @param U: an upper triangular matrix
 */
Vector UpperTriangleMatrixSolve(const Matrix &U, const Vector &b, bool isDiagonalUnit = false);

/*
 * Solve Lx = b, where L is a lower triangular matrix
 * TIME: O(n^2)
 * WARNING: This function will modify b
 *
 * @param L: a lower triangular matrix
 */
void LowerTriangleMatrixSolve_InPlace(const Matrix &L, Vector &b, bool isDiagonalUnit = false);

/*
 * Solve Ux = b, where U is an upper triangular matrix
 * TIME: O(n^2)
 * WARNING: This function will modify b
 *
 * @param U: an upper triangular matrix
 */
void UpperTriangleMatrixSolve_InPlace(const Matrix &U, Vector &b, bool isDiagonalUnit = false);

#endif //NUMERICAL_ALGEBRA_TRIANGLEMATRIX_H
