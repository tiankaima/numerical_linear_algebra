//
// Created by TianKai Ma on 2023/11/23.
//

#ifndef NUMERICAL_ALGEBRA_ITERATIONMETHOD_H
#define NUMERICAL_ALGEBRA_ITERATIONMETHOD_H

#include "CustomMath_lib.h"

#define ITERATION_METHOD_MAX_ITERATION 100000

typedef struct {
    Matrix A;
    Vector b;
    Vector x_default;
    lld precision_requirement;
} IterationMethodInput;

typedef struct {
    Vector x;
    int iteration_count;
    std::chrono::microseconds time_cost;
} IterationMethodOutput;

/// Solve Ax = b using Jacobi iteration method
IterationMethodOutput JacobiIteration(const IterationMethodInput &input);

/// Solve Ax = b using Gauss-Seidel iteration method
IterationMethodOutput GaussSeidelIteration(const IterationMethodInput &input);

/// Solve Ax = b using SOR iteration method
IterationMethodOutput SORIteration(const IterationMethodInput &input, lld omega);

/// Solve Ax = b using Conjugate Gradient iteration method
IterationMethodOutput ConjugateGradientMethod(const IterationMethodInput &input);

#endif //NUMERICAL_ALGEBRA_ITERATIONMETHOD_H
