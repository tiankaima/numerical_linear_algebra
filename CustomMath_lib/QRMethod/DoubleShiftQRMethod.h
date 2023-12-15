//
// Created by TianKai Ma on 2023/12/14.
//

#ifndef NUMERICAL_ALGEBRA_DOUBLESHIFTQRMETHOD_H
#define NUMERICAL_ALGEBRA_DOUBLESHIFTQRMETHOD_H

#include "CustomMath_lib.h"

/// P^T A P = H, returns H, P
Matrix DoubleShiftQRMethod(const Matrix &matrix);

/// P^T A P = H, returns H, P
Matrix DoubleStepQRIteration(Matrix &matrix, Matrix &P);

#endif //NUMERICAL_ALGEBRA_DOUBLESHIFTQRMETHOD_H
