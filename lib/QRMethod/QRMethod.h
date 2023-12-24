//
// Created by TianKai Ma on 2023/12/14.
//

#ifndef NUMERICAL_ALGEBRA_QRMETHOD_H
#define NUMERICAL_ALGEBRA_QRMETHOD_H

#include "DoubleShiftQRMethod.h"
#include "../../includes/NLAMethods.h"

typedef struct {
    lld real;
    lld complex;
} llc;

using MIterationMethodOutput = IterationMethodOutput<Matrix>;
using VIterationMethodOutput = IterationMethodOutput<Vector>;

MIterationMethodOutput QRMethod(const Matrix &matrix);

VIterationMethodOutput AllRootsForPolynomial(const Vector &coefficients);

std::vector<llc> AllEigenValues(const Matrix &R);

void print_llc(const std::vector<llc> &vec);

#endif //NUMERICAL_ALGEBRA_QRMETHOD_H
