//
// Created by TianKai Ma on 2023/12/18.
//

#ifndef NUMERICAL_ALGEBRA_JACOBIMETHOD_H
#define NUMERICAL_ALGEBRA_JACOBIMETHOD_H

#include "../../includes/NLAMethods.h"

typedef struct {
    Matrix A;
    Matrix P;
} JacobiMethodOutput;

using JIterationMethodOutput = IterationMethodOutput<JacobiMethodOutput>;

enum JacobiMethodType {
    JACOBI_METHOD_TYPE_CLASSIC, JACOBI_METHOD_TYPE_LOOP, JACOBI_METHOD_TYPE_THRESHOLD
};

/// P^T A P = H, returns H, P
/// A must be symmetric
JIterationMethodOutput JacobiMethod(const Matrix &matrix, JacobiMethodType type = JACOBI_METHOD_TYPE_CLASSIC);

#endif //NUMERICAL_ALGEBRA_JACOBIMETHOD_H
