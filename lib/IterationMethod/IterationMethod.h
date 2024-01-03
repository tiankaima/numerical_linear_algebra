//
// Created by TianKai Ma on 2023/11/23.
//

#ifndef NUMERICAL_ALGEBRA_ITERATIONMETHOD_H
#define NUMERICAL_ALGEBRA_ITERATIONMETHOD_H

#include "../../includes/NLAMethods.h"

typedef struct {
    const Matrix &A;
    const Vector &b;
    const Vector &x_default;
    lld precision_requirement;
} IterationMethodInput;

using VIterationMethodOutput = IterationMethodOutput<Vector>;

/// Solve Ax = b using Jacobi iteration method
VIterationMethodOutput JacobiIteration(const IterationMethodInput &input);

/// Solve Ax = b using Gauss-Seidel iteration method
VIterationMethodOutput GaussSeidelIteration(const IterationMethodInput &input);

/// Solve Ax = b using SOR iteration method
VIterationMethodOutput SORIteration(const IterationMethodInput &input, lld omega);

/// Solve Ax = b using Conjugate Gradient iteration method
VIterationMethodOutput ConjugateGradientMethod(const IterationMethodInput &input);

#endif //NUMERICAL_ALGEBRA_ITERATIONMETHOD_H
