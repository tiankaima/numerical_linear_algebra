//
// Created by tiankaima on 23-10-23.
//

#ifndef NUMERICAL_ALGEBRA_CHOLESKY_LDLT_H
#define NUMERICAL_ALGEBRA_CHOLESKY_LDLT_H

#include "vector"
#include "Vector/Vector.h"
#include "Matrix/Matrix.h"
#include "iostream"
#include "cmath"
#include "GaussMethod/TriangleMatrix.h"

void Cholesky_LDLT_Factorization(const Matrix &A, Matrix *L, Matrix *D);

void Cholesky_LDLT_Factorization_InPlace(Matrix &A);

Vector Cholesky_LDLT_Solve(const Matrix &A, const Vector &b);

void Cholesky_LDLT_Solve_InPlace(Matrix &A, Vector &b);

#endif //NUMERICAL_ALGEBRA_CHOLESKY_LDLT_H
