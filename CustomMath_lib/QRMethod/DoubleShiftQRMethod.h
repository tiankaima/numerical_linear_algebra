//
// Created by TianKai Ma on 2023/12/14.
//

#ifndef NUMERICAL_ALGEBRA_DOUBLESHIFTQRMETHOD_H
#define NUMERICAL_ALGEBRA_DOUBLESHIFTQRMETHOD_H

#include "CustomMath_lib.h"

typedef struct {
    Matrix H;
    Matrix P;
} DoubleShiftQRMethod_Result;

/// P^T A P = H, returns H, P
DoubleShiftQRMethod_Result DoubleShiftQRMethod(const Matrix &matrix);

#endif //NUMERICAL_ALGEBRA_DOUBLESHIFTQRMETHOD_H
