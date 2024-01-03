//
// Created by TianKai Ma on 2023/12/19.
//

#include "SVDMethod.h"


// SVD iteration with Wilkinson shift
// W(A) -> P, Q, B, s.t. B = P * A * Q
WilkinsonShift_Result WilkinsonShiftIteration(const Matrix &matrix) {
    auto B = Matrix(matrix);
    auto m = B.rows;
    auto n = B.cols;
    auto P = Matrix::identity(m);
    auto Q = Matrix::identity(n);

#define DELTA(i) B.matrix[i - 1][i - 1]
#define GAMMA(i) B.matrix[i - 1][i]
    auto alpha = DELTA(n) * DELTA(n) + GAMMA(n - 1) * GAMMA(n - 1);
    auto delta = (DELTA(n - 1) * DELTA(n - 1) + GAMMA(n - 2) * GAMMA(n - 2) - alpha) / 2;
    auto beta = DELTA(n - 1) * GAMMA(n - 1);
    auto mu = alpha - beta * beta / (delta + SIGN(delta) * std::sqrt(delta * delta + beta * beta));

    auto y = DELTA(1) * DELTA(1) - mu;
    auto z = DELTA(1) * GAMMA(1);
#undef DELTA
#undef GAMMA

    auto t = -z / y;
    auto c = 1 / std::sqrt(1 + t * t);
    auto s = c * t;

    auto G1 = RotationMatrix(n, 0, 1, c, s);
    B = B * G1;
    Q = Q * G1;

    for (ull k = 0; k < n - 1; k++) {
        t = -B.matrix[k + 1][k] / B.matrix[k][k]; // tan(theta)
        c = 1 / std::sqrt(1 + t * t); // cos(theta)
        s = c * t; // sin(theta)

        auto G = RotationMatrix(m, k, k + 1, c, s);
        B = G * B;
        P = G * P;


        if (k != n - 2) {
            t = B.matrix[k][k + 2] / B.matrix[k][k + 1]; // tan(theta)
            c = 1 / std::sqrt(1 + t * t); // cos(theta)
            s = c * t; // sin(theta)

            G = RotationMatrix(n, k + 1, k + 2, c, s);
            B = B * G;
            Q = Q * G;
        }
    }

    return {B, P, Q};
}

// Consider position k have DELTA(k + 1) = 0
// Then we can use Givens rotation to make GAMMA(k) = 0 as well:
ReformBidiagonalization_Result ReformBidiagonalization(const Matrix &matrix, ull k) {
    auto B = Matrix(matrix);
    auto m = B.rows;
    auto n = B.cols;
    auto G = Matrix::identity(m);

    B.print();

    for (ull i = k + 1; i < n; i++) {
        auto t = B.matrix[k][i] / B.matrix[i][i]; // tan(theta)
        auto c = 1 / std::sqrt(1 + t * t); // cos(theta)
        auto s = c * t; // sin(theta)

        G = RotationMatrix(m, k, i, c, s) * G;
        B = RotationMatrix(m, k, i, c, s) * B;

        B.print();
        G.print();
    }

    return {B, G};
}

SVDMethod_Result SVDMethod(const Matrix &matrix) {


}
