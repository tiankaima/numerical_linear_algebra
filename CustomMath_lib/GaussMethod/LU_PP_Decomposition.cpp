//
// Created by tiankaima on 23-10-23.
//

#include "LU_PP_Decomposition.h"

void LU_PP_Decomposition_InPlace(Matrix &A, Matrix &P) {
    CHECK_SQUARE_MATRIX(A)

    ull n = A.rows;
    P = Matrix::identity(n);

    for (ull i = 0; i < n; i++) {
        // find the pivot
        ull pivot_i = i;
        lld pivot = std::abs(A.matrix[i][i]);
        for (ull j = i; j < n; j++) {
            if (std::abs(A.matrix[j][i]) > std::abs(pivot)) {
                pivot = A.matrix[j][i];
                pivot_i = j;
            }
        }
        // swap rows
        if (pivot_i != i) {
            for (ull j = 0; j < n; j++) {
                std::swap(A.matrix[i][j], A.matrix[pivot_i][j]);
            }
        }

        // construct P
        std::swap(P.matrix[i], P.matrix[pivot_i]);

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

void LU_PP_Decomposition(const Matrix &A, Matrix &L, Matrix &U, Matrix &P) {
    CHECK_SQUARE_MATRIX(A)

    ull n = A.rows;
    L = Matrix(n, n);
    U = Matrix(A);
    LU_PP_Decomposition_InPlace(U, P);

    for (ull i = 0; i < n; i++) {
        L.matrix[i][i] = 1;
    }
    for (ull i = 0; i < n; i++) {
        for (ull j = 0; j < i; j++) {
            L.matrix[i][j] = U.matrix[i][j];
            U.matrix[i][j] = 0;
        }
    }
}

LU_PP_Decomposition_Result LU_PP_Decomposition(const Matrix &A) {
    CHECK_SQUARE_MATRIX(A)

    Matrix L, U, P;
    LU_PP_Decomposition(A, L, U, P);
    return {L, U, P};
}

void LU_PP_Solve_InPlace(Matrix &A, Vector &b) {
    CHECK_SQUARE_MATRIX(A)
    CHECK_EQUAL_SIZE(A, b)

    Matrix P;
    LU_PP_Decomposition_InPlace(A, P);
    Vector Pb = P * b; // fixme: this can be optimized since P only contains pivots
    Vector y = LowerTriangleMatrix_Solve(A, Pb, true);
    b = UpperTriangleMatrix_Solve(A, y);
}

Vector LU_PP_Solve(const Matrix &A, const Vector &b) {
    CHECK_SQUARE_MATRIX(A)
    CHECK_EQUAL_SIZE(A, b)

    Matrix A_copy = Matrix(A);
    Vector b_copy = Vector(b);
    LU_PP_Solve_InPlace(A_copy, b_copy);
    return b_copy;
}