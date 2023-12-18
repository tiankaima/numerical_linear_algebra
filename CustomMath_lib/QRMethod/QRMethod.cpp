//
// Created by TianKai Ma on 2023/12/14.
//

#include "QRMethod.h"

#define MAX_ITERATION 100000
#define ENABLE_TIMING

#ifdef ENABLE_TIMING
#define ITERATION_METHOD_TIMING_START auto start = std::chrono::high_resolution_clock::now();
#define ITERATION_METHOD_TIMING_END auto end = std::chrono::high_resolution_clock::now(); \
                  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
#define ITERATION_METHOD_RETURN_DURATION duration
#else
#define ITERATION_METHOD_TIMING_START
#define ITERATION_METHOD_TIMING_END
#define ITERATION_METHOD_RETURN_DURATION std::chrono::microseconds(0)
#endif

MIterationMethodOutput QRMethod(const Matrix &matrix) {
    Matrix H = matrix;
    Matrix Q;
    auto P = Matrix::identity(H.rows);
    auto n = H.rows;

    ITERATION_METHOD_TIMING_START

    HessenbergMethod_Inplace(H, Q);

    for (int count = 0; count < MAX_ITERATION; count++) {
        // set all abs(h_{i,i-1}) < 1e-10 to 0
        for (ull i = 0; i < H.rows - 1; i++) {
            if (std::abs(H.matrix[i + 1][i]) < 1e-6) {
                H.matrix[i + 1][i] = 0;
            }
        }
//        H.print();

        ull m = 0;
        ull k = 0;

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
        auto l = n - m - k;

        if (m == n || n - m - l <= 2) {
            ITERATION_METHOD_TIMING_END

            return { //
                    H.clean(), //
                    count, //
                    ITERATION_METHOD_RETURN_DURATION //
            };
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

    }

    throw std::runtime_error("QRMethod: iteration times exceed maximum");
}

VIterationMethodOutput AllRootsForPolynomial(const Vector &coefficients) {
    auto n = coefficients.size;
    auto A = Matrix(n, n);

    for (ull i = 0; i < n; i++) {
        A.matrix[i][0] = -coefficients.array[i];
    }

    for (ull i = 1; i < n; i++) {
        A.matrix[i - 1][i] = 1;
    }

    auto r = QRMethod(A); // assuming r is a diagonal matrix, which means all eigenvalues are real

    auto result = Vector(n);
    for (ull i = 0; i < n; i++) {
        result.array[i] = r.result.matrix[i][i];
    }

    return { //
            result, //
            r.iteration_count, //
            r.time_cost //
    };
}

std::vector<llc> AllEigenValues(const Matrix &R) {
    auto n = R.rows;
    auto result = std::vector<llc>(n);

    for (ull i = 0; i < n; i++) {
        if (i == n - 1 || R.matrix[i + 1][i] == 0) {
            result[i].real = R.matrix[i][i];
            result[i].complex = 0;
            continue;
        }

        auto a = R.matrix[i][i];
        auto b = R.matrix[i][i + 1];
        auto c = R.matrix[i + 1][i];
        auto d = R.matrix[i + 1][i + 1];

        auto delta = (a + d) * (a + d) - 4 * (a * d - b * c);
        if (delta >= 0) {
            result[i].real = (a + d + std::sqrt(delta)) / 2;
            result[i].complex = 0;
            result[i + 1].real = (a + d - std::sqrt(delta)) / 2;
            result[i + 1].complex = 0;
        } else {
            result[i].real = (a + d) / 2;
            result[i].complex = std::sqrt(-delta) / 2;
            result[i + 1].real = (a + d) / 2;
            result[i + 1].complex = -std::sqrt(-delta) / 2;
        }

        i++;
    }

    return result;
}

void print_llc(const std::vector<llc>& vec) {
    for (auto i: vec) {
        std::cout << i.real << " + " << i.complex << "i" << std::endl;
    }
}