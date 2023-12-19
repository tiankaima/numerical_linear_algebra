//
// Created by tiankaima on 23-11-2.
//

#ifndef NUMERICAL_ALGEBRA_HOUSEHOLDERMETHOD_H
#define NUMERICAL_ALGEBRA_HOUSEHOLDERMETHOD_H

#include "CustomMath_lib.h"

typedef struct {
    Vector v;
    lld beta;
} HouseHolder_Result;

typedef struct {
    Matrix Q;
    Matrix R;
} QR_Decomposition_Result;

/// Calculate the Householder vector v and the Householder constant beta
HouseHolder_Result HouseHolderMethod(const Vector &x);

/// Calculate the QR factorization of A = Q * [R; 0]^T
QR_Decomposition_Result QR_Decomposition(const Matrix &A);

/// Solve Ax = b using QR factorization
Vector QR_Solve(const Matrix &A, const Vector &b);

/// Calculate the QR factorization of A = Q * [R; 0]^T in place
void QR_Decomposition_InPlace(Matrix &A, Vector &d);

/// Solve Ax = b using QR factorization in place
void QR_Solve_InPlace(Matrix &A, Vector &b);

#endif //NUMERICAL_ALGEBRA_HOUSEHOLDERMETHOD_H
