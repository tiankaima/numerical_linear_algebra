//
// Created by TianKai Ma on 2023/12/19.
//

#ifndef NUMERICAL_ALGEBRA_BISECTMETHOD_H
#define NUMERICAL_ALGEBRA_BISECTMETHOD_H

#include "CustomMath_lib.h"

ull CalculateSignChange(const Vector &x, const Vector &y, lld mu);

Vector BisectMethod(const Vector &x, const Vector &y, lld precision = 1e-10);

#endif //NUMERICAL_ALGEBRA_BISECTMETHOD_H
