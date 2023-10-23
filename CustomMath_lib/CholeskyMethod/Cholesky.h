//
// Created by tiankaima on 23-10-23.
//

#ifndef NUMERICAL_ALGEBRA_CHOLESKY_H
#define NUMERICAL_ALGEBRA_CHOLESKY_H

#include "vector"
#include "Vector/Vector.h"
#include "Matrix/Matrix.h"
#include "iostream"
#include "cmath"
#include "GaussMethod/TriangleMatrix.h"

void CholeskyFactorization(const Matrix &A, Matrix *L);

void CholeskyFactorization_InPlace(Matrix &A);

Vector Cholesky_Solve(const Matrix &A, const Vector &b);

void Cholesky_Solve_InPlace(Matrix &A, Vector &b);

#endif //NUMERICAL_ALGEBRA_CHOLESKY_H
