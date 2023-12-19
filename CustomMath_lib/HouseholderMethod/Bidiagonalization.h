//
// Created by TianKai Ma on 2023/12/19.
//

#ifndef NUMERICAL_ALGEBRA_BIDIAGONALIZATION_H
#define NUMERICAL_ALGEBRA_BIDIAGONALIZATION_H

#include "CustomMath_lib.h"

typedef struct {
    Matrix B;
    Matrix U;
    Matrix V;
} Bidiagonalization_Result;

Bidiagonalization_Result BidiagonalizationMethod(const Matrix &matrix);

#endif //NUMERICAL_ALGEBRA_BIDIAGONALIZATION_H
