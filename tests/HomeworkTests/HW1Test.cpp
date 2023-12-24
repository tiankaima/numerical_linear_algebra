//
// Created by tiankaima on 23-12-16.
//

#include "../../includes/NLAMethods.h"
#include "../doctest.h"

Matrix m_1_1() {
    auto A = Matrix(84, 84);
    for (int i = 0; i < 84; i++) {
        A.matrix[i][i] = 6;
        if (i < 83) {
            A.matrix[i][i + 1] = 1;
            A.matrix[i + 1][i] = 8;
        }
    }
    return A;
}

Matrix m_1_2_1() {
    auto A = Matrix(100, 100);
    for (int i = 0; i < 100; i++) {
        A.matrix[i][i] = 10;
        if (i < 99) {
            A.matrix[i][i + 1] = 1;
            A.matrix[i + 1][i] = 1;
        }
    }
    return A;
}

Matrix m_1_2_2() {
    auto A = Matrix(40, 40);
    for (int i = 0; i < 40; i++) {
        A.matrix[i][i] = 1.0 / (i + 1);
        if (i < 39) {
            A.matrix[i][i + 1] = 1.0 / (i + 1);
            A.matrix[i + 1][i] = 1.0 / (i + 1);
        }
    }
    return A;
}

TEST_CASE("HW 1.1") {
    Matrix A;
    Vector b, x;

    A = m_1_1();

    b = Vector(84);
    for (int i = 1; i < 84 - 1; i++) {
        b.array[i] = 15;
    }
    b.array[0] = 7;
    b.array[84 - 1] = 14;

    x = LU_Solve(A, b);
    x = LU_FP_Solve(A, b);
    x = LU_PP_Solve(A, b);

    x = b;
    LU_Solve_InPlace(A, x);
    x = b;
    LU_FP_Solve_InPlace(A, x);
    x = b;
    LU_PP_Solve_InPlace(A, x);
}

TEST_CASE("HW 1.2") {
    Matrix A;
    Vector b, x;

    A = m_1_2_1();
    b = Vector(100);
    for (int i = 0; i < 100; i++) {
        b.array[i] = 1;
    }

    x = Cholesky_Solve(A, b);
    x = Cholesky_LDLT_Solve(A, b);

    x = b;
    Cholesky_Solve_InPlace(A, x);
    x = b;
    Cholesky_LDLT_Solve_InPlace(A, x);
}

TEST_CASE("HW 1.3(1)") {
    Matrix A;
    Vector b, x;

    A = m_1_2_1();

    b = Vector(100);
    for (int i = 0; i < 100; i++) {
        b.array[i] = 1;
    }

    x = LU_Solve(A, b);
    x = LU_FP_Solve(A, b);
    x = LU_PP_Solve(A, b);
    x = Cholesky_Solve(A, b);
    x = Cholesky_LDLT_Solve(A, b);

    x = b;
    LU_Solve_InPlace(A, x);
    x = b;
    LU_FP_Solve_InPlace(A, x);
    x = b;
    LU_PP_Solve_InPlace(A, x);
    x = b;
    Cholesky_Solve_InPlace(A, x);
    x = b;
    Cholesky_LDLT_Solve_InPlace(A, x);
}

TEST_CASE("HW 1.3(2)") {
    Matrix A;
    Vector b, x;

    A = m_1_2_2();

    b = Vector(40);
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++)
            b.array[i] += A.matrix[i][j];
    }

    x = LU_Solve(A, b);
    x = LU_FP_Solve(A, b);
    x = LU_PP_Solve(A, b);
    x = Cholesky_Solve(A, b);
    x = Cholesky_LDLT_Solve(A, b);

    x = b;
    LU_Solve_InPlace(A, x);
    x = b;
    LU_FP_Solve_InPlace(A, x);
    x = b;
    LU_PP_Solve_InPlace(A, x);
    x = b;
    Cholesky_Solve_InPlace(A, x);
    x = b;
    Cholesky_LDLT_Solve_InPlace(A, x);
}