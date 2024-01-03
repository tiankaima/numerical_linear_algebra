//
// Created by TianKai Ma on 2023/12/19.
//

#include "Bidiagonalization.h"

Bidiagonalization_Result BidiagonalizationMethod(const Matrix &matrix) {
#ifdef DEBUG
    if (matrix.rows < matrix.cols) {
        throw std::invalid_argument("BidiagonalizationMethod requires rows >= cols");
    }
#endif

    auto B = Matrix(matrix);
    auto m = B.rows;
    auto n = B.cols;
    auto U = Matrix::identity(m);
    auto V = Matrix::identity(n);

    for (ull k = 0; k < n; k++) {
        auto [v, beta] = HouseHolderMethod(B.sub_array_col(k, m, k));

        auto P = Matrix::identity(m);
        auto P_sub = Matrix::identity(m - k) - product(v, v) * beta;
        P.set(k, m, k, m, P_sub);
        U = P * U;

        auto A_sub = B.sub_matrix(k, m, k, n);
        A_sub = A_sub - product(v, v) * beta * A_sub;
        B.set(k, m, k, n, A_sub);

        if (k < n - 2) {
            auto [v, beta] = HouseHolderMethod(B.sub_array_row(k, k + 1, n));

            auto Q = Matrix::identity(n);
            auto Q_sub = Matrix::identity(n - k - 1) - product(v, v) * beta;
            Q.set(k + 1, n, k + 1, n, Q_sub);
            V = V * Q;

            auto A_sub = B.sub_matrix(k, m, k + 1, n);
            A_sub = A_sub - A_sub * product(v, v) * beta;
            B.set(k, m, k + 1, n, A_sub);
        }
    }

    return {B, U, V};
}