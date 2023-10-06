//
// Created by tiankaima on 23-10-5.
//

#ifndef NUMERICAL_ALGEBRA_CHOLESKYMETHOD_H
#define NUMERICAL_ALGEBRA_CHOLESKYMETHOD_H

#include "vector"
#include "Array.h"
#include "Matrix.h"
#include "iostream"
#include "cmath"
#include "GaussMethod.h"

// 1.3.1
Array CholeskySolve(const Matrix &A, const Array &b);

void CholeskyFactorization(const Matrix &A, Matrix *L);

void CholeskyFactorization_T(Matrix *A);

// 1.3.2
Array Cholesky_LDLT_Solve(const Matrix &A, const Array &b);

void Cholesky_LDLT_Factorization(const Matrix &A, Matrix *L, Matrix *D);

void Cholesky_LDLT_Factorization_T(Matrix *A);

#endif //NUMERICAL_ALGEBRA_CHOLESKYMETHOD_H
