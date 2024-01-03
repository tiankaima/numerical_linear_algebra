//
// Created by TianKai Ma on 2023/12/19.
//

#include "SVDMethod.h"

typedef struct {
    Matrix R;
    Matrix S;
} PolarDecomposition2D_Result;

PolarDecomposition2D_Result PolarDecomposition2D(const Matrix &A) {
    auto x = A.matrix[0][0] + A.matrix[1][1];
    auto y = A.matrix[1][0] - A.matrix[0][1];
    auto r = std::sqrt(x * x + y * y);
    auto c = x / r;
    auto s = y / r;
    auto R = Matrix(std::vector<std::vector<lld>>{
            {c, -s},
            {s, c}
    });
    auto S = R.transpose() * A;
    return {R, S};
}

WilkinsonShift_Result WilkinsonShiftIteration2D(const Matrix &A) {
    auto [R, S] = PolarDecomposition2D(A);
    auto V = Matrix::identity(2);
    lld c, s, sigma_1, sigma_2;

    if (S.matrix[0][1] == 0) {
        c = 1;
        s = 0;
        sigma_1 = S.matrix[0][0];
        sigma_2 = S.matrix[1][1];
    } else {
        auto tau = (S.matrix[0][0] - S.matrix[1][1]) / 2;
        auto omega = std::sqrt(tau * tau + S.matrix[0][1] * S.matrix[0][1]);
        auto t = S.matrix[0][1] / (tau + SIGN(tau) * omega);
        c = 1 / std::sqrt(1 + t * t);
        s = -c * t;
        sigma_1 = S.matrix[0][0] * c * c + S.matrix[1][1] * s * s - 2 * S.matrix[0][1] * c * s;
        sigma_2 = S.matrix[0][0] * s * s + S.matrix[1][1] * c * c + 2 * S.matrix[0][1] * c * s;
    }

    if (sigma_1 < sigma_2) {
        std::swap(sigma_1, sigma_2);
        V = Matrix(std::vector<std::vector<lld>>{
                {-s, c},
                {-c, -s}
        });
    } else {
        V = Matrix(std::vector<std::vector<lld>>{
                {c,  s},
                {-s, c}
        });
    }

    auto U = R * V;

    auto B = Matrix(std::vector<std::vector<lld>>{
            {sigma_1, 0},
            {0,       sigma_2}
    });

    return {B, U.transpose(), V};
}

// SVD iteration with Wilkinson shift
// W(A) -> P, Q, B, s.t. B = P * A * Q
WilkinsonShift_Result WilkinsonShiftIteration(const Matrix &matrix) {
    auto B = Matrix(matrix);
    auto m = B.rows;
    auto n = B.cols;
    auto P = Matrix::identity(m);
    auto Q = Matrix::identity(n);

    if (n == 2) {
        return WilkinsonShiftIteration2D(matrix);
    }

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

    for (ull i = k + 1; i < n; i++) {
        auto t = B.matrix[k][i] / B.matrix[i][i]; // tan(theta)
        auto c = 1 / std::sqrt(1 + t * t); // cos(theta)
        auto s = c * t; // sin(theta)

        G = RotationMatrix(m, k, i, c, s) * G;
        B = RotationMatrix(m, k, i, c, s) * B;
    }

    return {B, G};
}

SVDMethod_Result SVDMethod(const Matrix &matrix) {
#if DEBUG
    if (matrix.rows < matrix.cols) {
        throw std::invalid_argument("SVDMethod requires rows >= cols");
    }
#endif
    auto [B, U, V] = BidiagonalizationMethod(matrix); // B = U * A * V
    auto m = B.rows;
    auto n = B.cols;


    for (int count = 0; count < ITERATION_METHOD_MAX_ITERATION; count++) {
        // clean B:
        // TODO: Notice that these impl are not numerically stable, should be set to relative error
        for (ull i = 0; i < n - 1; i++) {
            if (std::abs(B.matrix[i][i + 1]) < 1e-8) {
                B.matrix[i][i + 1] = 0;
            }
        }

        for (ull i = 0; i < n; i++) {
            if (std::abs(B.matrix[i][i]) < 1e-8) {
                B.matrix[i][i] = 0;
            }
        }

        ull pivot_i = 0;
        ull pivot_j = 0;

        for (ull i = n - 1; i > 0; i--) {
            if (B.matrix[i - 1][i] != 0) {
                pivot_j = i + 1;
                break;
            }
        }

        if (pivot_j == 0) {
            return {B, U, V};
        }

        for (ull i = pivot_j - 1; i > 0; i--) {
            if (B.matrix[i - 1][i] == 0) {
                pivot_i = i;
                break;
            }
        }

        auto B22 = B.sub_matrix(pivot_i, pivot_j, pivot_i, pivot_j);

        ull k = 0;
        bool flag = false;
        // iterate over B22, if there's a B22_ii = 0, use ReformBidiagonalization:
        for (ull i = 0; i < B22.rows; i++) {
            if (B22.matrix[i][i] == 0) {
                flag = true;
                k = i;
                break;
            }
        }

        if (flag) {
            auto r = ReformBidiagonalization(B22, k);
            B.set(pivot_i, pivot_j, pivot_j, pivot_j, r.B);
            auto G_expanded = Matrix::identity(m);
            G_expanded.set(pivot_i, pivot_j, pivot_i, pivot_j, r.G);
            U = G_expanded * U;
        } else {
            auto r = WilkinsonShiftIteration(B22);
            B.set(pivot_i, pivot_j, pivot_i, pivot_j, r.B);

            auto U_expanded = Matrix::identity(m);
            U_expanded.set(pivot_i, pivot_j, pivot_i, pivot_j, r.P);
            U = U_expanded * U;

            auto V_expanded = Matrix::identity(n);
            V_expanded.set(pivot_i, pivot_j, pivot_i, pivot_j, r.Q);
            V = V * V_expanded;
        }
    }
}
