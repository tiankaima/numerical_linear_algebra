//
// Created by TianKai Ma on 2023/12/19.
//

#include "Bidiagonalization.h"

Bidiagonalization_Result BidiagonalizationMethod(const Matrix &matrix) {
#ifdef DEBUG
    if (matrix.rows < matrix.cols) {
        throw std::invalid_argument("BidiagonalizationMethod: rows < cols");
    }
#endif

    auto A = matrix;
    auto m = A.rows;
    auto n = A.cols;
    auto U = Matrix::identity(m);
    auto V = Matrix::identity(n);

    for (ull k = 0; k < n; k++) {
        auto x = A.sub_array_col(k, m, k);
        auto [v, beta] = HouseHolderMethod(x);

        auto P = Matrix::identity(m - k);
        P = P - product(v, v) * beta;

        auto P_extended = Matrix::identity(m);
        P_extended.set(k, m, k, m, P);

        A = P_extended.transpose() * A;
        U = U * P_extended;

        if (k < n - 2) {
            auto x = A.sub_array_row(k, k + 1, n);
            auto [v, beta] = HouseHolderMethod(x);

            auto Q = Matrix::identity(n - k - 1);
            Q = Q - product(v, v) * beta;

            auto Q_extended = Matrix::identity(n);
            Q_extended.set(k + 1, n, k + 1, n, Q);

            A = A * Q_extended;
            V = V * Q_extended;
        }
    }

    return {A, U, V};
}