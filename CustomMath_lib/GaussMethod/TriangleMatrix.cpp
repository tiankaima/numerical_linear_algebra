//
// Created by tiankaima on 23-10-23.
//

#include "TriangleMatrix.h"

void SolveLowerTriangleMatrix_InPlace(const Matrix &L, Vector &b) {
    CHECK_SQUARE_MATRIX_REF(L)

    for (unsigned int i = 0; i < b.size; i++) {
        b.array[i] = b.array[i] / L.matrix[i][i];
        for (unsigned int j = i + 1; j < b.size; j++) {
            b.array[j] -= L.matrix[j][i] * b.array[i];
        }
    }
}

void SolveUpperTriangleMatrix_InPlace(const Matrix &U, Vector &b) {
    CHECK_SQUARE_MATRIX_REF(U)

    for (unsigned int i = b.size - 1; i != -1; i--) {
        b.array[i] = b.array[i] / U.matrix[i][i];
        for (unsigned int j = i - 1; j != -1; j--) {
            b.array[j] -= U.matrix[j][i] * b.array[i];
        }
    }
}

Vector LowerTriangleMatrixSolve(const Matrix &L, const Vector &b) {
    auto x = Vector(b);
    SolveLowerTriangleMatrix_InPlace(L, x);
    return x;
}

Vector UpperTriangleMatrixSolve(const Matrix &U, const Vector &b) {
    auto x = Vector(b);
    SolveUpperTriangleMatrix_InPlace(U, x);
    return x;
}
