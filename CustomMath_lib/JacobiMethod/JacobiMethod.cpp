//
// Created by TianKai Ma on 2023/12/18.
//

#include "JacobiMethod.h"

Matrix JacobiRotationMatrix(ull n, ull p, ull q, lld c, lld s) {
    auto P = Matrix::identity(n);
    P.matrix[p][p] = c;
    P.matrix[q][q] = c;
    P.matrix[p][q] = -s;
    P.matrix[q][p] = s;

    return P;
}

typedef struct {
    ull p;
    ull q;
} JacobiIterationPivot;

JacobiIterationPivot JacobiIterationPivotFinder(const Matrix &A) {
    auto n = A.rows;
    ull p = 0, q = 1; // here i < j is always assumed
    lld pivot = std::abs(A.matrix[0][1]);
    for (ull i = 0; i < n; i++) {
        for (ull j = i + 1; j < n; j++) {
            if (std::abs(A.matrix[i][j]) > std::abs(pivot)) {
                pivot = A.matrix[i][j];
                p = i;
                q = j;
            }
        }
    }
    return {p, q};
}

std::optional<JacobiIterationPivot> JacobiIterationPivotFinder(const Matrix &A, lld threshold) {
    auto n = A.rows;
    for (ull i = 0; i < n; i++) {
        for (ull j = i + 1; j < n; j++) {
            if (std::abs(A.matrix[i][j]) > threshold) {
                return {JacobiIterationPivot{i, j}};
            }
        }
    }
    return std::nullopt;
}

void JacobiIteration(ull n, Matrix &A, Matrix &P, JacobiIterationPivot pivot) {
    auto p = pivot.p;
    auto q = pivot.q;

    auto a_pp = A.matrix[p][p];
    auto a_qq = A.matrix[q][q];
    auto a_pq = A.matrix[p][q];

    auto rho = (a_pp - a_qq) / (2 * a_pq);

    auto t = SIGN(rho) / (std::abs(rho) + std::sqrt(1 + rho * rho)); // tan(theta)
    auto c = 1 / std::sqrt(1 + t * t); // cos(theta)
    auto s = c * t; // sin(theta)


    auto J = JacobiRotationMatrix(n, p, q, c, s);
    P = P * J;

    // manually calculate A = P^T A P to speed up
    A.matrix[p][p] = c * c * a_pp + s * s * a_qq + 2 * c * s * a_pq; // beta_pp
    A.matrix[q][q] = s * s * a_pp + c * c * a_qq - 2 * c * s * a_pq; // beta_qq
    A.matrix[p][q] = 0; // beta_pq
    A.matrix[q][p] = 0; // beta_qp


    // update beta_ip and beta_iq
    for (ull i = 0; i < n; i++) {
        if (i != p && i != q) {
            auto a_ip = A.matrix[i][p];
            auto a_iq = A.matrix[i][q];
            A.matrix[i][p] = c * a_ip + s * a_iq;
            A.matrix[p][i] = A.matrix[i][p];
            A.matrix[i][q] = c * a_iq - s * a_ip;
            A.matrix[q][i] = A.matrix[i][q];
        }
    }
}

JIterationMethodOutput JacobiMethod(const Matrix &matrix, JacobiMethodType type) {
    auto n = matrix.rows;
    auto A = matrix;
    auto P = Matrix::identity(n);

    if (type == JACOBI_METHOD_TYPE_CLASSIC) {
        auto iteration_count = 0;
        ITERATION_METHOD_TIMING_START

        while (true) {
            auto pivot = JacobiIterationPivotFinder(A);
            JacobiIteration(n, A, P, pivot);
            iteration_count++;

            if (MatrixNorm_E(A) < 1e-10) {

                ITERATION_METHOD_TIMING_END

                return {A, P, iteration_count, ITERATION_METHOD_RETURN_DURATION};
            }
        }
    } else if (type == JACOBI_METHOD_TYPE_LOOP) {
        auto iteration_count = 0;
        ITERATION_METHOD_TIMING_START

        while (true) {
            for (ull i = 0; i < n - 1; i++) {
                for (ull j = i + 1; j < n; j++) {
                    auto pivot = JacobiIterationPivot{i, j};
                    JacobiIteration(n, A, P, pivot);
                    iteration_count++;

                    if (MatrixNorm_E(A) < 1e-10) {

                        ITERATION_METHOD_TIMING_END

                        return {A, P, iteration_count, ITERATION_METHOD_RETURN_DURATION};
                    }
                }
            }
        }
    } else if (type == JACOBI_METHOD_TYPE_THRESHOLD) {
        auto delta = MatrixNorm_E(A);
        auto iteration_count = 0;

        ITERATION_METHOD_TIMING_START

        while (delta > 1e-10) {
            while (true) {
                auto pivot = JacobiIterationPivotFinder(A, delta);
                if (pivot.has_value()) {
                    iteration_count++;
                    JacobiIteration(n, A, P, pivot.value());
                } else {
                    break;
                }
            }

            delta /= 10;
        }

        ITERATION_METHOD_TIMING_END

        return {A, P, iteration_count, ITERATION_METHOD_RETURN_DURATION};
    }
}