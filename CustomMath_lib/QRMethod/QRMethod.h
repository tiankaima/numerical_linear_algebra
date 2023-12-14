//
// Created by TianKai Ma on 2023/12/14.
//

#ifndef NUMERICAL_ALGEBRA_QRMETHOD_H
#define NUMERICAL_ALGEBRA_QRMETHOD_H

#include "Matrix/Matrix.h"
#include "Vector/Vector.h"
#include "chrono"
#include "HouseholderMethod/HouseholderMethod.h"
#include "DoubleStepQRIteration.h"
#include "HouseholderMethod/HessenbergMethod.h"

typedef struct {
    lld real;
    lld complex;
} llc;

template<typename T>
struct QRMethodOutput {
    T result;
    int iteration_times;
    std::chrono::microseconds time_cost;
};


QRMethodOutput<Matrix> QRMethod(const Matrix &matrix);

QRMethodOutput<Vector> AllRootsForPolynomial(const Vector &coefficients);

std::vector<llc> AllEigenValues(const Matrix &R);

void print_llc(const std::vector<llc> vec);

#endif //NUMERICAL_ALGEBRA_QRMETHOD_H
