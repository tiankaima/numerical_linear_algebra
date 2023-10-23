//
// Created by tiankaima on 23-10-23.
//

#ifndef NUMERICAL_ALGEBRA_LU_PP_H
#define NUMERICAL_ALGEBRA_LU_PP_H

#include "iostream"
#include "vector"
#include "Vector/Vector.h"
#include "Matrix/Matrix.h"
#include "GaussMethod/TriangleMatrix.h"

/*
 * LU factorization with partial pivoting
 * TIME: O(n^3)
 *
 * @param A: a square matrix
 * @param L: a lower triangle matrix, det(L) == 1
 * @param U: a upper triangle matrix
 * @param P: a permutation matrix
 */
void LU_PP_Factorization(const Matrix &A, Matrix *L, Matrix *U, Matrix *P);

/*
 * LU factorization with partial pivoting
 * TIME: O(n^3)
 *
 * WARNING:
 * This function will modify A, which stores both L and U
 *
 * @param A: a square matrix
 * @param P: a permutation matrix
 */
void LU_PP_Factorization_InPlace(Matrix &A, Matrix *P);

/*
 * Solve Ax = b using LU decomposition with full pivoting
 * TIME: O(n^3)
 *
 * @param A: a square matrix
 * @param b: a vector
 */
Vector LU_PP_Solve(const Matrix &A, const Vector &b);

/*
 * Solve Ax = b using LU decomposition with full pivoting
 * TIME: O(n^3)
 *
 * WARNING: This function will modify A and b
 *
 * @param A: a square matrix
 * @param b: a vector
 */
void LU_PP_Solve_InPlace(Matrix &A, Vector &b);

#endif //NUMERICAL_ALGEBRA_LU_PP_H
