//
// Created by TianKai Ma on 2023/12/19.
//

#ifndef NUMERICAL_ALGEBRA_SVDMETHOD_H
#define NUMERICAL_ALGEBRA_SVDMETHOD_H

#include "../../includes/NLAMethods.h"

typedef struct {
    Matrix B;
    Matrix U;
    Matrix V;
} SVDMethod_Result;

SVDMethod_Result SVDMethod(const Matrix &matrix);

typedef struct {
    Matrix B;
    Matrix P;
    Matrix Q;
} WilkinsonShift_Result;

WilkinsonShift_Result WilkinsonShiftIteration2D(const Matrix &A);

WilkinsonShift_Result WilkinsonShiftIteration(const Matrix &matrix);

typedef struct {
    Matrix B;
    Matrix G;
} ReformBidiagonalization_Result;

ReformBidiagonalization_Result ReformBidiagonalization(const Matrix &matrix, ull k);


#endif //NUMERICAL_ALGEBRA_SVDMETHOD_H
