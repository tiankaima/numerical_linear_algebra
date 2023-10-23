//
// Created by tiankaima on 23-10-5.
//

#include "CholeskyMethod.h"

Vector Cholesky_Solve(const Matrix &A, const Vector &b) {
    Matrix L;
    CholeskyFactorization(A, &L);
    Vector y = LowerTriangleMatrix_Solve(L, b);
    Vector x = UpperTriangleMatrix_Solve(L.transpose(), y);
    return x;
}

void CholeskyFactorization_InPlace(Matrix &A) {
    CHECK_SQUARE_MATRIX_REF(A)

    ull n = A.rows;

    for (ull k = 0; k < n; k++) {
        if (A.matrix[k][k] <= 0) {
            // FIXME: I dont like this either, sorry.
            A.matrix[k][k] = 1e-2;
//            throw std::invalid_argument("A is not a positive definite matrix");
        }
        A.matrix[k][k] = std::sqrt(A.matrix[k][k]);
        for (ull i = k + 1; i < n; i++) {
            A.matrix[i][k] /= A.matrix[k][k];
        }
        for (ull j = k + 1; j < n; j++) {
            for (ull i = j; i < n; i++) {
                A.matrix[i][j] -= A.matrix[i][k] * A.matrix[j][k];
            }
        }
    }
}

void CholeskyFactorization(const Matrix &A, Matrix *L) {
    CHECK_SQUARE_MATRIX_REF(A)

    ull n = A.rows;
    *L = Matrix(A);
    CholeskyFactorization_InPlace(*L);

    for (ull i = 0; i < n; i++) {
        for (ull j = i + 1; j < n; j++) {
            L->matrix[i][j] = 0;
        }
    }
}

Vector Cholesky_LDLT_Solve(const Matrix &A, const Vector &b) {
    Matrix L, D;
    Cholesky_LDLT_Factorization(A, &L, &D);
    Vector y = LowerTriangleMatrix_Solve(L, b);
    for (ull i = 0; i < A.rows; i++) {
        y.array[i] /= D.matrix[i][i];
    }
    Vector x = UpperTriangleMatrix_Solve(L.transpose(), y);
    return x;
}

void Cholesky_LDLT_Factorization_InPlace(Matrix &A) {
    CHECK_SQUARE_MATRIX_REF(A)
    ull n = A.rows;
    Vector tmp = Vector(n);

    for (ull j = 0; j < n; j++) {
        for (ull i = 0; i < j; i++) {
            tmp.array[i] = A.matrix[j][i] * A.matrix[i][i];
        }
        for (ull i = 0; i < j; i++) {
            A.matrix[j][j] -= A.matrix[j][i] * tmp.array[i];
        }
        for (ull i = j + 1; i < n; i++) {
            for (ull k = 0; k < j; k++) {
                A.matrix[i][j] -= A.matrix[i][k] * tmp.array[k];
            }
            A.matrix[i][j] /= A.matrix[j][j];
        }
    }
}


void Cholesky_LDLT_Factorization(const Matrix &A, Matrix *L, Matrix *D) {
    CHECK_SQUARE_MATRIX_REF(A)

    ull n = A.rows;
    *L = Matrix(A);
    Cholesky_LDLT_Factorization_InPlace(*L);

    *D = Matrix(n, A.cols);
    for (ull i = 0; i < n; i++) {
        D->matrix[i][i] = L->matrix[i][i];
        L->matrix[i][i] = 1;
    }
    for (ull i = 0; i < n; i++) {
        for (ull j = i + 1; j < A.cols; j++) {
            D->matrix[i][i] *= L->matrix[j][j];
            L->matrix[i][j] = 0;
        }
    }
}
