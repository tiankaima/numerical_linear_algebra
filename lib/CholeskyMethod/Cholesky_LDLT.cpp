//
// Created by tiankaima on 23-10-23.
//

#include "Cholesky_LDLT.h"

void Cholesky_LDLT_Decomposition_InPlace(Matrix &A) {
    CHECK_SQUARE_MATRIX(A)

    auto n = A.rows;
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


Cholesky_LDLT_Result Cholesky_LDLT_Decomposition(const Matrix &A) {
    CHECK_SQUARE_MATRIX(A)

    auto n = A.rows;
    auto L = Matrix(A);
    Cholesky_LDLT_Decomposition_InPlace(L);

    auto D = Matrix(n, n);
    for (ull i = 0; i < n; i++) {
        D.matrix[i][i] = L.matrix[i][i];
        L.matrix[i][i] = 1;
    }
    for (ull i = 0; i < n; i++) {
        for (ull j = i + 1; j < n; j++) {
            D.matrix[i][i] *= L.matrix[j][j];
            L.matrix[i][j] = 0;
        }
    }

    return {L, D};
}

Vector Cholesky_LDLT_Solve(const Matrix &A, const Vector &b) {
    CHECK_SQUARE_MATRIX(A)

    auto tmp = Cholesky_LDLT_Decomposition(A);
    auto L = tmp.L;
    auto D = tmp.D;

    auto y = LowerTriangleMatrix_Solve(L, b);
    for (ull i = 0; i < A.rows; i++) {
        y.array[i] /= D.matrix[i][i];
    }
    auto x = UpperTriangleMatrix_Solve(L.transpose(), y);
    return x;
}

void Cholesky_LDLT_Solve_InPlace(Matrix &A, Vector &b) {
    CHECK_SQUARE_MATRIX(A)
    CHECK_EQUAL_SIZE(A, b)

    Cholesky_LDLT_Decomposition_InPlace(A);
    LowerTriangleMatrix_Solve_InPlace(A, b, true);
    for (ull i = 0; i < A.rows; i++) {
        b.array[i] /= A.matrix[i][i];
    }
    UpperTriangleMatrix_Solve_InPlace(A.transpose(), b, true);
}
