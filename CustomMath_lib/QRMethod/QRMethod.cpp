//
// Created by TianKai Ma on 2023/12/14.
//

#include "QRMethod.h"

Matrix QRMethod(const Matrix &matrix) {
    Matrix H = matrix;
    Matrix Q;
    auto P = Matrix::identity(H.rows);
    auto n = H.rows;

    HessenbergMethod_Inplace(H, Q);

    do {
        // set all abs(h_{i,i-1}) < 1e-10 to 0
        for (ull i = 0; i < H.rows - 1; i++) {
            if (std::abs(H.matrix[i + 1][i]) < 1e-6) {
                H.matrix[i + 1][i] = 0;
            }
        }
        H.print();

        ull m = 0;
        ull k = 0;
        ull l = 0;

        for (ull i = H.rows - 1; i != -1; i--) {
            if (i != 0) {
                if (H.matrix[i][i - 1] == 0) {
                    m++;
                    continue;
                } else {
                    if (i == 1 || H.matrix[i - 1][i - 2] == 0) {
                        m++;
                        continue;
                    } else {
                        break;
                    }
                }
            } else {
                m++;
            }
        }

        for (ull i = n - m - 1; i != -1; i--) {
            k++;
            if (i != 0) {
                if (H.matrix[i][i - 1] == 0) {
                    break;
                }
            }
        }
        l = n - m - k;

        if (m == n || n - m - l <= 2) {
            break;
        }

        auto H22 = H.sub_matrix(l, n - m, l, n - m);
        H22 = DoubleStepQRIteration(H22, P);
        H.set(l, n - m, l, n - m, H22);

        auto Q_tmp = Matrix::identity(n);
        Q_tmp.set(l, n - m, l, n - m, P);
        Q = Q * Q_tmp;

        auto H12 = H.sub_matrix(0, l, l, n - m);
        auto H23 = H.sub_matrix(l, n - m, n - m, n);
        H12 = H12 * P;
        H23 = P.transpose() * H23;
        H.set(0, l, l, n - m, H12);
        H.set(l, n - m, n - m, n, H23);

    } while (true);

    return H.clean();
}