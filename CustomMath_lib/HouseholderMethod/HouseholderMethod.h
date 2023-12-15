//
// Created by tiankaima on 23-11-2.
//

#ifndef NUMERICAL_ALGEBRA_HOUSEHOLDERMETHOD_H
#define NUMERICAL_ALGEBRA_HOUSEHOLDERMETHOD_H

#include "CustomMath_lib.h"

void HouseHolderMethod(const Vector &x, Vector &v, lld &beta);

void QRFactorization_InPlace(Matrix &A, Vector &d);

void QRFactorization(const Matrix &A, Matrix &Q, Matrix &R);

Vector QR_Solve(const Matrix &A, const Vector &b);

void QR_Solve_InPlace(Matrix &A, Vector &b);

#endif //NUMERICAL_ALGEBRA_HOUSEHOLDERMETHOD_H
