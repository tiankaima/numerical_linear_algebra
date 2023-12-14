//
// Created by TianKai Ma on 2023/12/14.
//

#ifndef NUMERICAL_ALGEBRA_QRMETHOD_H
#define NUMERICAL_ALGEBRA_QRMETHOD_H

#include "Matrix/Matrix.h"
#include "Vector/Vector.h"
#include "HouseholderMethod/HouseholderMethod.h"
#include "DoubleStepQRIteration.h"
#include "HouseholderMethod/HessenbergMethod.h"

typedef struct {
    lld real;
    lld complex;
} llc;

Matrix QRMethod(const Matrix &matrix);
Vector AllRootsForPolynomial(const Vector &coefficients);
std::vector<llc> AllEigenValues(const Matrix &R);
void print_llc(const std::vector<llc> vec);

#endif //NUMERICAL_ALGEBRA_QRMETHOD_H
