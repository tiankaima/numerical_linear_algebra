//
// Created by TianKai Ma on 2023/12/19.
//

#ifndef NUMERICAL_ALGEBRA_SVDMETHOD_H
#define NUMERICAL_ALGEBRA_SVDMETHOD_H

#include "../../includes/NLAMethods.h"

typedef struct {
    Matrix U;
    Matrix S;
    Matrix V;
} SVDMethod_Result;


typedef struct {
    Matrix B;
    Matrix P;
    Matrix Q;
} WilkinsonShift_Result;

WilkinsonShift_Result WilkinsonShiftIteration(const Matrix &matrix);

typedef struct {
    Matrix B;
    Matrix G;
} ReformBidiagonalization_Result;

ReformBidiagonalization_Result ReformBidiagonalization(const Matrix &matrix, ull k);


#endif //NUMERICAL_ALGEBRA_SVDMETHOD_H
