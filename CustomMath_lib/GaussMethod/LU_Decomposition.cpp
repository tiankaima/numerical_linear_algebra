//
// Created by tiankaima on 23-10-23.
//

#include "LU_Decomposition.h"

void LU_Decomposition_InPlace(Matrix &A) {
    CHECK_SQUARE_MATRIX(A)

    ull n = A.rows;

    for (ull i = 0; i < n - 1; i++) {
        for (ull j = i + 1; j < n; j++) {
            A.matrix[j][i] /= A.matrix[i][i];

            for (ull k = i + 1; k < n; k++) {
                A.matrix[j][k] -= A.matrix[j][i] * A.matrix[i][k];
            }
        }
    }
}

void LU_Decomposition(const Matrix &A, Matrix &L, Matrix &U) {
    CHECK_SQUARE_MATRIX(A)

    ull n = A.rows;
    L = Matrix(n, n);
    U = Matrix(A);
    LU_Decomposition_InPlace(U);

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

LU_Decomposition_Result LU_Decomposition(const Matrix &A) {
    CHECK_SQUARE_MATRIX(A)

    Matrix L, U;
    LU_Decomposition(A, L, U);
    return {L, U};
}

void LU_Solve_InPlace(Matrix &A, Vector &b) {
    CHECK_SQUARE_MATRIX(A)
    CHECK_EQUAL_SIZE(A, b)

    LU_Decomposition_InPlace(A);
    LowerTriangleMatrix_Solve_InPlace(A, b, true);
    UpperTriangleMatrix_Solve_InPlace(A, b);
}

Vector LU_Solve(const Matrix &A, const Vector &b) {
    CHECK_SQUARE_MATRIX(A)
    CHECK_EQUAL_SIZE(A, b)

    Matrix A_copy = Matrix(A);
    Vector b_copy = Vector(b);
    LU_Solve_InPlace(A_copy, b_copy);
    return b_copy;
}