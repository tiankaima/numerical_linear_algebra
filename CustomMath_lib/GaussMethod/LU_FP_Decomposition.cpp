//
// Created by tiankaima on 23-10-23.
//

#include "LU_FP_Decomposition.h"

LU_FP_Decomposition_Inplace_Result LU_FP_Decomposition_InPlace(Matrix &A) {
    CHECK_SQUARE_MATRIX(A)

    auto n = A.rows;
    auto P = Matrix::identity(n);
    auto Q = Matrix::identity(n);

    for (ull i = 0; i < n; i++) {
        // find the pivot
        ull pivot_i = i, pivot_j = i;
        lld pivot = std::abs(A.matrix[i][i]);
        for (ull j = i; j < n; j++) {
            for (ull k = i; k < n; k++) {
                if (std::abs(A.matrix[j][k]) > std::abs(pivot)) {
                    pivot = A.matrix[j][k];
                    pivot_i = j;
                    pivot_j = k;
                }
            }
        }
        // swap rows
        if (pivot_i != i) {
            for (ull j = 0; j < n; j++) {
                std::swap(A.matrix[i][j], A.matrix[pivot_i][j]);
            }
        }
        // swap columns
        if (pivot_j != i) {
            for (ull j = 0; j < n; j++) {
                std::swap(A.matrix[j][i], A.matrix[j][pivot_j]);
            }
        }

        // construct P and Q
        std::swap(P.matrix[i], P.matrix[pivot_i]);
        std::swap(Q.matrix[i], Q.matrix[pivot_j]);

        if (pivot == 0) {
            throw std::invalid_argument("A is singular");
        }

        // do the elimination
        for (ull j = i + 1; j < n; j++) {
            A.matrix[j][i] /= A.matrix[i][i];
            for (ull k = i + 1; k < n; k++) {
                A.matrix[j][k] -= A.matrix[j][i] * A.matrix[i][k];
            }
        }
    }

    return {P, Q};
}

LU_FP_Decomposition_Result LU_FP_Decomposition(const Matrix &A) {
    CHECK_SQUARE_MATRIX(A)

    auto n = A.rows;
    auto L = Matrix(n, n);
    auto U = Matrix(A);
    auto [P, Q] = LU_FP_Decomposition_InPlace(U);

    for (ull i = 0; i < n; i++) {
        L.matrix[i][i] = 1;
    }
    for (ull i = 0; i < n; i++) {
        for (ull j = 0; j < i; j++) {
            L.matrix[i][j] = U.matrix[i][j];
            U.matrix[i][j] = 0;
        }
    }

    return {L, U, P, Q};
}

void LU_FP_Solve_InPlace(Matrix &A, Vector &b) {
    CHECK_SQUARE_MATRIX(A)
    CHECK_EQUAL_SIZE(A, b)

    auto [P, Q] = LU_FP_Decomposition_InPlace(A);
    auto Pb = P * b;
    auto UQix = LowerTriangleMatrix_Solve(A, Pb, true);
    auto Qix = UpperTriangleMatrix_Solve(A, UQix);
    b = Q * Qix;
}

Vector LU_FP_Solve(const Matrix &A, const Vector &b) {
    CHECK_SQUARE_MATRIX(A)
    CHECK_EQUAL_SIZE(A, b)

    auto A_copy = Matrix(A);
    auto b_copy = Vector(b);
    LU_FP_Solve_InPlace(A_copy, b_copy);
    return b_copy;
}