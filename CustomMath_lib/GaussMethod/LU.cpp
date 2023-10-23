//
// Created by tiankaima on 23-10-23.
//

#include "LU.h"

void LU_Factorization_InPlace(Matrix &A) {
    CHECK_SQUARE_MATRIX_REF(A)

    for (int i = 0; i < A.rows - 1; i++) {
        for (int j = i + 1; j < A.rows; j++) {
            A.matrix[j][i] /= A.matrix[i][i];

            for (int k = i + 1; k < A.rows; k++) {
                A.matrix[j][k] -= A.matrix[j][i] * A.matrix[i][k];
            }
        }
    }
}

void LU_Factorization(const Matrix &A, Matrix *L, Matrix *U) {
    *U = Matrix(A);
    LU_Factorization_InPlace(*U);
    *L = Matrix(A.rows, A.cols);

    for (int i = 0; i < A.rows; i++) {
        L->matrix[i][i] = 1;
    }

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < i; j++) {
            L->matrix[i][j] = U->matrix[i][j];
            U->matrix[i][j] = 0;
        }
    }
}

void LU_Solve_InPlace(Matrix &A, Vector &b) {
    CHECK_EQUAL_SIZE_REF(A, b)

    LU_Factorization_InPlace(A);
    // FIXME: THIS CLEARLY DOESN'T WORK SINCE L[i][i] != 1
    SolveLowerTriangleMatrix_InPlace(A, b);
    SolveUpperTriangleMatrix_InPlace(A, b);
}

Vector LU_Solve(const Matrix &A, const Vector &b) {
    Matrix L, U;
    LU_Factorization(A, &L, &U);
    Vector y = LowerTriangleMatrixSolve(L, b);
    Vector x = UpperTriangleMatrixSolve(U, y);
    return x;
}