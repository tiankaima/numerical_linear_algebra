//
// Created by TianKai Ma on 2023/12/14.
//

#ifndef NUMERICAL_ALGEBRA_POWERITERATION_H
#define NUMERICAL_ALGEBRA_POWERITERATION_H

#include "CustomMath_lib.h"

typedef struct {
    const Matrix &A;
    const Vector &x_default;
    int iteration_times;
} PowerIterationInput;

using PowerIterationOutput = IterationMethodOutput<lld>;
using RevPowerIterationOutput = IterationMethodOutput<Vector>;

/// \brief: Find the max eigenvalue for a matrix using power iteration method
PowerIterationOutput PowerIteration(const PowerIterationInput &input);

/// \brief: Find the min eigenvalue for a matrix using reverse power iteration method
RevPowerIterationOutput RevPowerIteration(const PowerIterationInput &input);

/// \brief: Find the max root for a polynomial using power iteration method
/// \param: coefficients: The coefficients of the polynomial, x^n + a_{1}x^{n-1} + ... + a_{n-1}x + a_{n} is assumed
/// \return: The max root for the polynomial
PowerIterationOutput MaxRootForPolynomial(const Vector &coefficients);

#endif //NUMERICAL_ALGEBRA_POWERITERATION_H
