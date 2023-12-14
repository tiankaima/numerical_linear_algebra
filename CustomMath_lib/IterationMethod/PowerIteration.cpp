//
// Created by TianKai Ma on 2023/12/14.
//

#include "PowerIteration.h"

lld PowerIteration(const PowerIterationInput &input) {
    auto A = input.A;
    auto x = input.x_default;
    for (int i = 0; i < input.iteration_times; i++) {
        x = x / VectorNorm_Infinity(x);
        x = A * x;
    }
    return VectorNorm_Infinity(x);
}

lld MaxRootForPolynomial(const Vector &coefficients) {
    auto n = coefficients.size;
    auto A = Matrix(n, n);

    for (ull i = 0; i < n; i++) {
        A.matrix[i][0] = -coefficients.array[i];
    }

    for (ull i = 1; i < n; i++) {
        A.matrix[i - 1][i] = 1;
    }

    auto x = Vector(n, 0);
    x.array[0] = 1;

    auto result = PowerIteration({A, x, 100000});
    return result;
}