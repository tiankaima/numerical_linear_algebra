//
// Created by tiankaima on 23-10-23.
//

#include "Cholesky.h"

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

Vector Cholesky_Solve(const Matrix &A, const Vector &b) {
    Matrix L;
    CholeskyFactorization(A, &L);
    Vector y = LowerTriangleMatrix_Solve(L, b);
    Vector x = UpperTriangleMatrix_Solve(L.transpose(), y);
    return x;
}