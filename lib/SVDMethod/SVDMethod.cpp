//
// Created by TianKai Ma on 2023/12/19.
//

#include "SVDMethod.h"


// SVD iteration with Wilkinson shift
WilkinsonShift_Result WilkinsonShiftIteration(const Matrix &matrix) {
    auto B = Matrix(matrix);
    auto n = B.rows;
    auto P = Matrix::identity(n);
    auto Q = Matrix::identity(n);

#define DELTA(i) B.matrix[i - 1][i - 1]
#define GAMMA(i) B.matrix[i - 1][i]

    auto alpha = DELTA(n) * DELTA(n) + GAMMA(n - 1) * GAMMA(n - 1);
    auto delta = (DELTA(n - 1) * DELTA(n - 1) + GAMMA(n - 2) * GAMMA(n - 2) - alpha) / 2;
    auto beta = DELTA(n - 1) * GAMMA(n - 1);
    auto mu = alpha - beta * beta / (delta + SIGN(delta) * std::sqrt(delta * delta + beta * beta));

    auto y = DELTA(1) * DELTA(1) - mu;
    auto z = DELTA(1) * GAMMA(1);

    for (ull k = 0; k < n; k++) {
        auto t = -z / y; // tan(theta)
        auto c = 1 / std::sqrt(1 + t * t); // cos(theta)
        auto s = c * t; // sin(theta)

        Q = Q * RotationMatrix(n, k + 1, k + 2, c, s);

        y = c * DELTA(k + 1) - s * GAMMA(k + 1);
        z = -s * DELTA(k + 2);
        GAMMA(k + 1) = s * DELTA(k + 1) + c * GAMMA(k + 1);
        DELTA(k + 2) = c * DELTA(k + 2);

        t = -z / y; // tan(theta)
        c = 1 / std::sqrt(1 + t * t); // cos(theta)
        s = c * t; // sin(theta)

        P = RotationMatrix(n, k + 1, k + 2, c, s) * P;
        if (k != n - 1) {
            y = c * GAMMA(k + 1) - s * DELTA(k + 2);
            z = -s * GAMMA(k + 2);
            DELTA(k + 1) = s * GAMMA(k + 1) + c * DELTA(k + 2);
            GAMMA(k + 2) = c * GAMMA(k + 2);
        } else {
            auto gamma_k = GAMMA(k + 1);
            auto delta_k = DELTA(k + 2);

            GAMMA(k + 1) = c * gamma_k - s * delta_k;
            DELTA(k + 2) = s * gamma_k + c * delta_k;
        }
    }

    return {B, P, Q};
#undef DELTA
#undef GAMMA
}

// Consider position k have DELTA(k + 1) = 0
// Then we can use Givens rotation to make GAMMA(k) = 0 as well:
ReformBidiagonalization_Result ReformBidiagonalization(const Matrix &matrix, ull k) {
    auto B = Matrix(matrix);
    auto n = B.rows;
    auto G = Matrix::identity(n);

    B.print();

    for (ull i = k + 1; i < B.cols; i++) {
        auto t = B.matrix[k][i] / B.matrix[i][i] ; // tan(theta)
        auto c = 1 / std::sqrt(1 + t * t); // cos(theta)
        auto s = c * t; // sin(theta)

        G = RotationMatrix(n, k, i, c, s) * G;
        B = RotationMatrix(n, k, i, c, s) * B;

        B.print();
        G.print();
    }

    return {B, G};
}

//SVDMethod_Result SVDMethod(const Matrix &matrix) {
//
//}
