//
// Created by tiankaima on 23-10-23.
//

#include "Cholesky_LDLT.h"

void Cholesky_LDLT_Factorization_InPlace(Matrix &A) {
    CHECK_SQUARE_MATRIX(A)

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
    CHECK_SQUARE_MATRIX(A)

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
