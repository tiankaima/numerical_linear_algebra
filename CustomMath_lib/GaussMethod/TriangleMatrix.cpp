//
// Created by tiankaima on 23-10-23.
//

#include "TriangleMatrix.h"

void LowerTriangleMatrix_Solve_InPlace(const Matrix &L, Vector &b, bool isDiagonalUnit) {
    CHECK_SQUARE_MATRIX(L)
    CHECK_EQUAL_SIZE(L, b)

    for (ull i = 0; i < b.size; i++) {
        if (!isDiagonalUnit) b.array[i] = b.array[i] / L.matrix[i][i];

        for (ull j = i + 1; j < b.size; j++) {
            b.array[j] -= L.matrix[j][i] * b.array[i];
        }
    }
}

void UpperTriangleMatrix_Solve_InPlace(const Matrix &U, Vector &b, bool isDiagonalUnit) {
    CHECK_SQUARE_MATRIX(U)
    CHECK_EQUAL_SIZE(U, b)

    for (ull i = U.cols - 1; i != -1; i--) {
        if (!isDiagonalUnit) b.array[i] = b.array[i] / U.matrix[i][i];

        for (ull j = i - 1; j != -1; j--) {
            b.array[j] -= U.matrix[j][i] * b.array[i];
        }
    }
}

Vector LowerTriangleMatrix_Solve(const Matrix &L, const Vector &b, bool isDiagonalUnit) {
    CHECK_SQUARE_MATRIX(L)
    CHECK_EQUAL_SIZE(L, b)

    auto x = Vector(b);
    LowerTriangleMatrix_Solve_InPlace(L, x, isDiagonalUnit);
    return x;
}

Vector UpperTriangleMatrix_Solve(const Matrix &U, const Vector &b, bool isDiagonalUnit) {
    CHECK_SQUARE_MATRIX(U)
    CHECK_EQUAL_SIZE(U, b)

    auto x = Vector(b);
    UpperTriangleMatrix_Solve_InPlace(U, x, isDiagonalUnit);
    return x;
}
