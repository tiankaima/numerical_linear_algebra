//
// Created by tiankaima on 23-10-23.
//

#include "LU_PP.h"

void LU_PP_Factorization_InPlace(Matrix *A, Matrix *P) {
    CHECK_SQUARE_MATRIX(A)

    // init P
    *P = Matrix::identity(A->rows);

    for (int i = 0; i < A->rows; i++) {
        // find the pivot
        int pivot_i = i;
        long double pivot = std::abs(A->matrix[i][i]);
        for (int j = i; j < A->rows; j++) {
            if (std::abs(A->matrix[j][i]) > std::abs(pivot)) {
                pivot = A->matrix[j][i];
                pivot_i = j;
            }
        }
        // swap rows
        if (pivot_i != i) {
            for (int j = 0; j < A->rows; j++) {
                std::swap(A->matrix[i][j], A->matrix[pivot_i][j]);
            }
        }

        // construct P
        std::swap(P->matrix[i], P->matrix[pivot_i]);

        if (pivot == 0) {
            throw std::invalid_argument("A is singular");
        }

        // do the elimination
        for (int j = i + 1; j < A->rows; j++) {
            A->matrix[j][i] /= A->matrix[i][i];
            for (int k = i + 1; k < A->rows; k++) {
                A->matrix[j][k] -= A->matrix[j][i] * A->matrix[i][k];
            }
        }
    }
}

void LU_PP_Factorization(const Matrix &A, Matrix *L, Matrix *U, Matrix *P) {
    *U = Matrix(A);
    LU_PP_Factorization_InPlace(U, P);
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

Vector LU_PP_Solve(const Matrix &A, const Vector &b) {
    Matrix L, U, P;
    LU_PP_Factorization(A, &L, &U, &P);
    Vector Pb = P * b;
    Vector y = LowerTriangleMatrixSolve(L, Pb);
    Vector x = UpperTriangleMatrixSolve(U, y);
    return x;
}