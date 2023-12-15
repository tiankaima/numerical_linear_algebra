//
// Created by TianKai Ma on 2023/12/14.
//

#include "DoubleShiftQRMethod.h"

Matrix DoubleShiftQRMethod(const Matrix &matrix) {
    auto H = HessenbergMethod(matrix).H;

    auto n = matrix.rows;
    auto m = n - 1;
    auto s = H.matrix[m - 1][m - 1] + H.matrix[n - 1][n - 1];
    auto t = H.matrix[m - 1][m - 1] * H.matrix[n - 1][n - 1] - H.matrix[m - 1][n - 1] * H.matrix[n - 1][m - 1];
    auto x = H.matrix[0][0] * H.matrix[0][0] + H.matrix[0][1] * H.matrix[1][0] - s * H.matrix[0][0] + t;
    auto y = H.matrix[1][0] * (H.matrix[0][0] + H.matrix[1][1] - s);
    auto z = H.matrix[1][0] * H.matrix[2][1];

    Vector b;
    lld beta;

    for (ull k = 0; k < n - 2; k++) {
        auto tmpVector = Vector(std::vector<lld>{x, y, z});
        HouseHolderMethod(tmpVector, b, beta);
        auto w = product(b, b) * beta;

        auto q = MAX(1, k);
        auto H_sub = H.sub_matrix(k, k + 3, q - 1, n);
        H_sub = H_sub - w * H_sub;
        H.set(k, k + 3, q - 1, n, H_sub);

        auto r = MIN(k + 3, n);
        H_sub = H.sub_matrix(0, r, k, k + 3);
        H_sub = H_sub - H_sub * w;
        H.set(0, r, k, k + 3, H_sub);

        x = H.matrix[k + 1][k];
        y = H.matrix[k + 2][k];
        if (k < n - 3) {
            z = H.matrix[k + 3][k];
        }
    }
    auto tmpVector = Vector(std::vector<lld>{x, y});
    HouseHolderMethod(tmpVector, b, beta);
    auto w = product(b, b) * beta;

    auto H_sub = H.sub_matrix(n - 2, n, n - 3, n);
    H_sub = H_sub - w * H_sub;
    H.set(n - 2, n, n - 3, n, H_sub);

    H_sub = H.sub_matrix(0, n, n - 2, n);
    H_sub = H_sub - H_sub * w;
    H.set(0, n, n - 2, n, H_sub);

    return H.clean();
}

Matrix DoubleStepQRIteration(Matrix &matrix, Matrix &P) {
    // init P:
    P = Matrix::identity(matrix.rows);

    auto H = HessenbergMethod(matrix).H;

    auto n = matrix.rows;
    auto m = n - 1;
    auto s = H.matrix[m - 1][m - 1] + H.matrix[n - 1][n - 1];
    auto t = H.matrix[m - 1][m - 1] * H.matrix[n - 1][n - 1] - H.matrix[m - 1][n - 1] * H.matrix[n - 1][m - 1];
    auto x = H.matrix[0][0] * H.matrix[0][0] + H.matrix[0][1] * H.matrix[1][0] - s * H.matrix[0][0] + t;
    auto y = H.matrix[1][0] * (H.matrix[0][0] + H.matrix[1][1] - s);
    auto z = H.matrix[1][0] * H.matrix[2][1];

    Vector b;
    lld beta;

    for (ull k = 0; k < n - 2; k++) {
        auto tmpVector = Vector(std::vector<lld>{x, y, z});
        HouseHolderMethod(tmpVector, b, beta);
        auto w = product(b, b) * beta;

        auto q = MAX(1, k);
        auto H_sub = H.sub_matrix(k, k + 3, q - 1, n);
        H_sub = H_sub - w * H_sub;
        H.set(k, k + 3, q - 1, n, H_sub);

        auto r = MIN(k + 3, n);
        H_sub = H.sub_matrix(0, r, k, k + 3);
        H_sub = H_sub - H_sub * w;
        H.set(0, r, k, k + 3, H_sub);

        auto P_sub = P.sub_matrix(0, n, k, k + 3);
        P_sub = P_sub - P_sub * w;
        P.set(0, n, k, k + 3, P_sub);

        x = H.matrix[k + 1][k];
        y = H.matrix[k + 2][k];
        if (k < n - 3) {
            z = H.matrix[k + 3][k];
        }
    }
    auto tmpVector = Vector(std::vector<lld>{x, y});
    HouseHolderMethod(tmpVector, b, beta);
    auto w = product(b, b) * beta;

    auto H_sub = H.sub_matrix(n - 2, n, n - 3, n);
    H_sub = H_sub - w * H_sub;
    H.set(n - 2, n, n - 3, n, H_sub);

    H_sub = H.sub_matrix(0, n, n - 2, n);
    H_sub = H_sub - H_sub * w;
    H.set(0, n, n - 2, n, H_sub);

    return H.clean();
}