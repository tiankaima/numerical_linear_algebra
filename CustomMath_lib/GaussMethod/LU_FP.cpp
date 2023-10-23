//
// Created by tiankaima on 23-10-23.
//

#include "LU_FP.h"

void LU_FP_Factorization_InPlace(Matrix &A, Matrix *P, Matrix *Q) {
    CHECK_SQUARE_MATRIX_REF(A)
    unsigned long int n = A.rows;

    // init P and Q
    *P = Matrix::identity(n);
    *Q = Matrix::identity(n);

    for (int i = 0; i < n; i++) {
        // find the pivot
        int pivot_i = i, pivot_j = i;
        long double pivot = std::abs(A.matrix[i][i]);
        for (int j = i; j < n; j++) {
            for (int k = i; k < n; k++) {
                if (std::abs(A.matrix[j][k]) > std::abs(pivot)) {
                    pivot = A.matrix[j][k];
                    pivot_i = j;
                    pivot_j = k;
                }
            }
        }
        // swap rows
        if (pivot_i != i) {
            for (int j = 0; j < n; j++) {
                std::swap(A.matrix[i][j], A.matrix[pivot_i][j]);
            }
        }
        // swap columns
        if (pivot_j != i) {
            for (int j = 0; j < n; j++) {
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
        for (int j = i + 1; j < n; j++) {
            A.matrix[j][i] /= A.matrix[i][i];
            for (int k = i + 1; k < n; k++) {
                A.matrix[j][k] -= A.matrix[j][i] * A.matrix[i][k];
            }
        }
    }
}

void LU_FP_Factorization(const Matrix &A, Matrix *L, Matrix *U, Matrix *P, Matrix *Q) {
    *U = Matrix(A);
    LU_FP_Factorization_InPlace(*U, P, Q);
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

Vector LU_FP_Solve(const Matrix &A, const Vector &b) {
    Matrix L, U, P, Q;
    LU_FP_Factorization(A, &L, &U, &P, &Q);
    Vector Pb = P * b;
    Vector UQix = LowerTriangleMatrixSolve(L, Pb);
    Vector Qix = UpperTriangleMatrixSolve(U, UQix);
    Vector x = Q * Qix;
    return x;
}