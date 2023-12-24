//
// Created by TianKai Ma on 2023/12/19.
//

#include "SVDMethod.h"

typedef struct {
    Matrix B;
    Matrix P;
    Matrix Q;
} WilkinsonShift_Result;

// SVD iteration with Wilkinson shift
WilkinsonShift_Result WilkinsonShiftIteration(const Matrix &matrix) {
    auto B = Matrix(matrix);
    auto n = B.rows;
    auto P = Matrix::identity(n);
    auto Q = Matrix::identity(n);

    // delta_n ^ 2 + gamma_(n-1) ^ 2
    auto alpha = B.matrix[n - 1][n - 1] * B.matrix[n - 1][n - 1] + B.matrix[n - 2][n - 1] * B.matrix[n - 2][n - 1];
    // (delta_(n-1) ^ 2 + gamma_(n-1) ^ 2 - alpha)/ 2
    auto delta = (B.matrix[n - 2][n - 2] * B.matrix[n - 2][n - 2] + B.matrix[n - 2][n - 1] * B.matrix[n - 2][n - 1] -
                  alpha) / 2;
    // delta_(n-1) * gamma_(n-1)
    auto beta = B.matrix[n - 2][n - 2] * B.matrix[n - 2][n - 1];

    auto mu = alpha - beta * beta / (delta + SIGN(delta) * sqrt(delta * delta + beta * beta));
    auto y = B.matrix[0][0] * B.matrix[0][0] - mu;
    auto z = B.matrix[0][0] * B.matrix[0][1];

    for (ull k = 0; k < n - 1; k++) {
        auto tmpVector = Vector(std::vector<lld>{y, z});
        auto [b, beta] = HouseHolderMethod(tmpVector);
        auto w = product(b, b) * beta;

        auto q = MAX(1, k);
        auto B_sub = B.sub_matrix(k, k + 2, q - 1, n);
        B_sub = B_sub - w * B_sub;
        B.set(k, k + 2, q - 1, n, B_sub);

        auto r = MIN(k + 2, n);
        B_sub = B.sub_matrix(0, r, k, k + 2);
        B_sub = B_sub - B_sub * w;
        B.set(0, r, k, k + 2, B_sub);

        auto P_sub = P.sub_matrix(0, n, k, k + 2);
        P_sub = P_sub - P_sub * w;
        P.set(0, n, k, k + 2, P_sub);

        y = B.matrix[k + 1][k];
        if (k < n - 2) {
            z = B.matrix[k + 2][k];
        }
    }
}