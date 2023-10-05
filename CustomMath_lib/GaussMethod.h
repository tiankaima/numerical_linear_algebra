//
// Created by tiankaima on 23-10-5.
//

#ifndef NUMERICAL_ALGEBRA_GAUSSMETHOD_H
#define NUMERICAL_ALGEBRA_GAUSSMETHOD_H

#include "vector"
#include "Array.h"
#include "Matrix.h"

// 1.1.1
Array LowerGaussSolve(const Matrix &A, const Array &b);

void LowerGaussSolve_T(const Matrix &A, Array &b);

// 1.1.2
Array UpperGaussSolve(const Matrix &A, const Array &b);

void UpperGaussSolve_T(const Matrix &A, Array &b);

// 1.1.3
void LU_Factorization(const Matrix &A, Matrix *L, Matrix *U);

void LU_Factorization_T(Matrix *A);

// 1.2.1
void LU_FP_Factorization(const Matrix &A, Matrix *L, Matrix *U, Matrix *P, Matrix *Q);

void LU_FP_Factorization_T(Matrix *A, Matrix *P, Matrix *Q);

// 1.2.2
void LU_PP_Factorization(const Matrix &A, Matrix *L, Matrix *U, Matrix *P);

void LU_PP_Factorization_T(Matrix *A, Matrix *P);

#endif //NUMERICAL_ALGEBRA_GAUSSMETHOD_H
