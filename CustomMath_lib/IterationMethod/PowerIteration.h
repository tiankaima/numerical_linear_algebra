//
// Created by TianKai Ma on 2023/12/14.
//

#ifndef NUMERICAL_ALGEBRA_POWERITERATION_H
#define NUMERICAL_ALGEBRA_POWERITERATION_H

#include "Matrix/Matrix.h"
#include "Vector/Vector.h"
#include "chrono"
#include "InfinityNorm/InfinityNorm.h"

typedef struct {
    const Matrix &A;
    const Vector &x_default;
    int iteration_times;
} PowerIterationInput;

typedef struct {
    lld x;
    int iteration_times;
    std::chrono::microseconds time_cost;
} PowerIterationOutput;

PowerIterationOutput PowerIteration(const PowerIterationInput &input);

/*
 * @brief: Find the max root for a polynomial
 *
 * @param: coefficients: The coefficients of the polynomial, x^n + a_{1}x^{n-1} + ... + a_{n-1}x + a_{n} is assumed
 * @return: The max root for the polynomial
 */
PowerIterationOutput MaxRootForPolynomial(const Vector &coefficients);

#endif //NUMERICAL_ALGEBRA_POWERITERATION_H
