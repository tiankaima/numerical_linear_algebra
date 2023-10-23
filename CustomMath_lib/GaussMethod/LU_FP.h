//
// Created by tiankaima on 23-10-23.
//

#ifndef NUMERICAL_ALGEBRA_LU_FP_H
#define NUMERICAL_ALGEBRA_LU_FP_H

#include "iostream"
#include "vector"
#include "Vector/Vector.h"
#include "Matrix/Matrix.h"
#include "GaussMethod/TriangleMatrix.h"

/*
 * LU factorization with full pivoting
 * TIME: O(n^3)
 *
 *
 * WARNING:
 * @param A: a square matrix
 * @param L: a lower triangle matrix, det(L) == 1
 * @param U: a upper triangle matrix
 * @param P: a permutation matrix
 * @param Q: a permutation matrix
 */
void LU_FP_Factorization(const Matrix &A, Matrix *L, Matrix *U, Matrix *P, Matrix *Q);

/*
 * LU factorization with full pivoting
 * TIME: O(n^3)
 *
 * WARNING:
 * This function will modify A, which stores both L and U
 *
 * @param A: a square matrix
 * @param P: a permutation matrix
 * @param Q: a permutation matrix
 */
void LU_FP_Factorization_InPlace(Matrix &A, Matrix *P, Matrix *Q);

/*
 * Solve Ax = b using LU decomposition with full pivoting
 * TIME: O(n^3)
 *
 * @param A: a square matrix
 * @param b: a vector
 */
Vector LU_FP_Solve(const Matrix &A, const Vector &b);


/*
 * Solve Ax = b using LU decomposition with full pivoting
 * TIME: O(n^3)
 *
 * WARNING: This function will modify A and b
 *
 * @param A: a square matrix
 * @param b: a vector
 */
void LU_FP_Solve_InPlace(Matrix &A, Vector &b);

#endif //NUMERICAL_ALGEBRA_LU_FP_H
