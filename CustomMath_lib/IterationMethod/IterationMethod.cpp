//
// Created by TianKai Ma on 2023/11/23.
//

#include "IterationMethod.h"

#define ENABLE_ITERATION_METHOD_TIMING

#ifdef ENABLE_ITERATION_METHOD_TIMING
#define ITERATION_METHOD_TIMING_START auto start = std::chrono::high_resolution_clock::now();
#define ITERATION_METHOD_TIMING_END auto end = std::chrono::high_resolution_clock::now(); \
                  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
#define ITERATION_METHOD_RETURN_DURATION duration
#else
#define ITERATION_METHOD_TIMING_START
#define ITERATION_METHOD_TIMING_END
#define ITERATION_METHOD_RETURN_DURATION std::chrono::microseconds(0)
#endif

IterationMethodOutput JacobiIteration(const IterationMethodInput &input) {
    auto A = input.A;
    auto x = input.x_default;
    auto D = A.sub_diagonal();
    auto L = A.sub_lowerTriangle();
    auto U = A.sub_upperTriangle();

    ITERATION_METHOD_TIMING_START

    auto D_inv = D.diagonal_inverse();
    auto B = D_inv * (L + U) * -1;
    auto g = D_inv * input.b;

    for (int i = 0; i < ITERATION_METHOD_MAX_ITERATION; i++) {
        auto x_new = B * x + g;
        if ((x_new - x).norm() < input.precision_requirement) {

            ITERATION_METHOD_TIMING_END

            return {
                    x_new,
                    i,
                    ITERATION_METHOD_RETURN_DURATION
            };
        }
        x = x_new;
    }

    throw std::invalid_argument("JacobiIteration: iteration count exceeds ITERATION_METHOD_MAX_ITERATION");
}

IterationMethodOutput GaussSeidelIteration(const IterationMethodInput &input) {
    auto A = input.A;
    auto x = input.x_default;
    auto D = A.sub_diagonal();
    auto L = A.sub_lowerTriangle();
    auto U = A.sub_upperTriangle();

    ITERATION_METHOD_TIMING_START

    auto D_L = D + L;
    auto g = LowerTriangleMatrix_Solve(D_L, input.b);

    for (int i = 0; i < ITERATION_METHOD_MAX_ITERATION; i++) {
        auto x_new = g - LowerTriangleMatrix_Solve(D_L, U * x);
        if ((x_new - x).norm() < input.precision_requirement) {
            ITERATION_METHOD_TIMING_END

            return {
                    x_new,
                    i,
                    ITERATION_METHOD_RETURN_DURATION
            };
        }
        x = x_new;
    }

    throw std::invalid_argument("GaussSeidelIteration: iteration count exceeds ITERATION_METHOD_MAX_ITERATION");
}

IterationMethodOutput SORIteration(const IterationMethodInput &input, lld omega) {
    auto A = input.A;
    auto x = input.x_default;
    auto D = A.sub_diagonal();
    auto L = A.sub_lowerTriangle();
    auto U = A.sub_upperTriangle();

    ITERATION_METHOD_TIMING_START

    auto D_L = D + L;
    auto g = LowerTriangleMatrix_Solve(D_L, input.b);

    for (int i = 0; i < ITERATION_METHOD_MAX_ITERATION; i++) {
        auto tmp = g - LowerTriangleMatrix_Solve(D_L, U * x);
        auto x_new = x * (1 - omega) + tmp * omega;
        if ((x_new - x).norm() < input.precision_requirement) {
            ITERATION_METHOD_TIMING_END

            return {
                    x_new,
                    i,
                    ITERATION_METHOD_RETURN_DURATION
            };
        }
        x = x_new;
    }

    throw std::invalid_argument("SORIteration: iteration count exceeds ITERATION_METHOD_MAX_ITERATION");
}