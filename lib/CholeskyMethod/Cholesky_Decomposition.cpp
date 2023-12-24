//
// Created by tiankaima on 23-10-23.
//

#include "Cholesky_Decomposition.h"

void Cholesky_Decomposition_InPlace(Matrix &A) {
    CHECK_SQUARE_MATRIX(A)

    auto n = A.rows;

    for (ull k = 0; k < n; k++) {
//        if (A.matrix[k][k] <= 0) {
        // FIXME: I dont like this either, sorry.
//            A.matrix[k][k] = 1e-2;
//            throw std::invalid_argument("A is not a positive definite matrix");
//        }
        A.matrix[k][k] = std::sqrt(std::abs(A.matrix[k][k]));
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

Matrix Cholesky_Decomposition(const Matrix &A) {
    CHECK_SQUARE_MATRIX(A)

    auto n = A.rows;
    auto L = Matrix(A);
    Cholesky_Decomposition_InPlace(L);

    for (ull i = 0; i < n; i++) {
        for (ull j = i + 1; j < n; j++) {
            L.matrix[i][j] = 0;
        }
    }

    return L;
}

Vector Cholesky_Solve(const Matrix &A, const Vector &b) {
    auto L = Cholesky_Decomposition(A);
    auto y = LowerTriangleMatrix_Solve(L, b);
    auto x = UpperTriangleMatrix_Solve(L.transpose(), y);
    return x;
}

void Cholesky_Solve_InPlace(Matrix &A, Vector &b) {
    Cholesky_Decomposition_InPlace(A);
    LowerTriangleMatrix_Solve_InPlace(A, b);
    UpperTriangleMatrix_Solve_InPlace(A.transpose(), b);
}