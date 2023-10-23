//
// Created by tiankaima on 23-10-23.
//

#ifndef NUMERICAL_ALGEBRA_LU_H
#define NUMERICAL_ALGEBRA_LU_H


#include "iostream"
#include "vector"
#include "Vector/Vector.h"
#include "Matrix/Matrix.h"
#include "GaussMethod/TriangleMatrix.h"

/*
 * LU factorization A = LU
 * TIME: O(2/3 * n^3)
 *
 * @param A: a square matrix
 * @param L: a lower triangle matrix, det(L) == 1
 * @param U: a upper triangle matrix
 */
void LU_Factorization(const Matrix &A, Matrix *L, Matrix *U);

/*
 * LU factorization A = LU
 * TIME: O(2/3 * n^3)
 *
 * WARNING:
 * This function will modify A, which stores both L and U
 * since det(L) == 1 (the diagonal elements of L are all 1)
 * here A[i][i] is the diagonal element of U
 *
 * @param A: a square matrix
 */
void LU_Factorization_InPlace(Matrix &A);

/*
 * Solve Ax = b using LU decomposition
 * TIME: O(n^3)
 *
 * @param A: a square matrix
 * @param b: a vector
 */
Vector LU_Solve(const Matrix &A, const Vector &b);

/*
 * Solve Ax = b using LU decomposition
 * TIME: O(n^3)
 *
 * WARNING: This function will modify A, which stores both L and U
 *
 * @param A: a square matrix
 * @param b: a vector
 */
void LU_Solve_InPlace(Matrix &A, Vector &b);

#endif //NUMERICAL_ALGEBRA_LU_H
