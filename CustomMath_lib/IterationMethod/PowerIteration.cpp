//
// Created by TianKai Ma on 2023/12/14.
//

#include "PowerIteration.h"

#define ITERATION_METHOD_MAX_ITERATION 100000

#define ENABLE_POWER_ITERATION_METHOD_TIMING

#ifdef ENABLE_POWER_ITERATION_METHOD_TIMING
#define ITERATION_METHOD_TIMING_START auto start = std::chrono::high_resolution_clock::now();
#define ITERATION_METHOD_TIMING_END auto end = std::chrono::high_resolution_clock::now(); \
                  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
#define ITERATION_METHOD_RETURN_DURATION duration
#else
#define ITERATION_METHOD_TIMING_START
#define ITERATION_METHOD_TIMING_END
#define ITERATION_METHOD_RETURN_DURATION std::chrono::microseconds(0)
#endif

PowerIterationOutput PowerIteration(const PowerIterationInput &input) {
    auto A = input.A;
    auto x = input.x_default;

    ITERATION_METHOD_TIMING_START

    for (int i = 0; i < input.iteration_times; i++) {
        x = x / VectorNorm_Infinity(x);
        x = A * x;
    }

    ITERATION_METHOD_TIMING_END

    return { //
            VectorNorm_Infinity(x), //
            input.iteration_times, //
            ITERATION_METHOD_RETURN_DURATION //
    };
}

PowerIterationOutput MaxRootForPolynomial(const Vector &coefficients) {
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

    return PowerIteration({A, x, ITERATION_METHOD_MAX_ITERATION});
}