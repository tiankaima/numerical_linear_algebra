//
// Created by TianKai Ma on 2023/11/23.
//

#ifndef NUMERICAL_ALGEBRA_ITERATIONMETHOD_H
#define NUMERICAL_ALGEBRA_ITERATIONMETHOD_H

#include "Vector/Vector.h"
#include "Matrix/Matrix.h"
#include "chrono"
#include "GaussMethod/GaussMethod.h"

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

IterationMethodOutput JacobiIteration(const IterationMethodInput &input);

IterationMethodOutput GaussSeidelIteration(const IterationMethodInput &input);

IterationMethodOutput SORIteration(const IterationMethodInput &input, lld omega);

IterationMethodOutput ConjugateGradientMethod(const IterationMethodInput &input);

#endif //NUMERICAL_ALGEBRA_ITERATIONMETHOD_H
