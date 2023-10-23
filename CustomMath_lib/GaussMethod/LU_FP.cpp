//
// Created by tiankaima on 23-10-23.
//

#include "LU_FP.h"

void LU_FP_Factorization_InPlace(Matrix &A, Matrix *P, Matrix *Q) {
    CHECK_SQUARE_MATRIX(A)

    ull n = A.rows;
    *P = Matrix::identity(n);
    *Q = Matrix::identity(n);

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
        std::swap(P->matrix[i], P->matrix[pivot_i]);
        std::swap(Q->matrix[i], Q->matrix[pivot_j]);

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
}

void LU_FP_Factorization(const Matrix &A, Matrix *L, Matrix *U, Matrix *P, Matrix *Q) {
    CHECK_SQUARE_MATRIX(A)

    ull n = A.rows;
    *L = Matrix(n, n);
    *U = Matrix(A);
    LU_FP_Factorization_InPlace(*U, P, Q);

    for (ull i = 0; i < n; i++) {
        L->matrix[i][i] = 1;
    }
    for (ull i = 0; i < n; i++) {
        for (ull j = 0; j < i; j++) {
            L->matrix[i][j] = U->matrix[i][j];
            U->matrix[i][j] = 0;
        }
    }
}

void LU_FP_Solve_InPlace(Matrix &A, Vector &b) {
    CHECK_SQUARE_MATRIX(A)
    CHECK_EQUAL_SIZE(A, b)

    Matrix P, Q;
    LU_FP_Factorization_InPlace(A, &P, &Q);
    Vector Pb = P * b;
    Vector UQix = LowerTriangleMatrix_Solve(A, Pb, true);
    Vector Qix = UpperTriangleMatrix_Solve(A, UQix);
    b = Q * Qix;
}

Vector LU_FP_Solve(const Matrix &A, const Vector &b) {
    CHECK_SQUARE_MATRIX(A)
    CHECK_EQUAL_SIZE(A, b)

    Matrix A_copy = Matrix(A);
    Vector b_copy = Vector(b);
    LU_FP_Solve_InPlace(A_copy, b_copy);
    return b_copy;
}