//
// Created by tiankaima on 23-12-16.
//

#include "CustomMath_lib.h"
#include "../doctest.h"

Matrix A_1() {
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

Vector x_1() {
    auto x = Vector(84, 1);
    return x;
}

Vector b_1() {
    auto b = Vector(84);
    for (int i = 1; i < 84 - 1; i++) {
        b.array[i] = 15;
    }
    b.array[0] = 7;
    b.array[84 - 1] = 14;
    return b;
}

Matrix A_2() {
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

Vector x_2() {
    auto x = Vector(100, 1);
    return x;
}

Vector b_2() {
    auto b = Vector(100);
    for (int i = 1; i < 100 - 1; i++) {
        b.array[i] = 12;
    }
    b.array[0] = 11;
    b.array[100 - 1] = 11;
    return b;
}

Matrix A_3() {
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

Vector x_3() {
    auto x = Vector(40, 1);
    return x;
}

Vector b_3() {
    auto b = Vector(40);
    auto A = A_3();
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            b.array[i] += A.matrix[i][j];
        }
    }
    return b;
}

Vector t_22() {
    return Vector(std::vector<lld>{-1, -0.75, -0.5, 0, 0.25, 0.5, 0.75});
}

Vector y_22() {
    return Vector(std::vector<lld>{1, 0.8125, 0.75, 1, 1.3125, 1.75, 2.3125});
}

Matrix A_33() {
    return Matrix(std::vector<std::vector<lld>>{{1, 4.9176,  1,   3.472,  0.998, 1,   7,  4, 42, 3, 1, 0},
                                                {1, 5.0208,  1,   3.531,  1.5,   2,   7,  4, 62, 1, 1, 0},
                                                {1, 4.5429,  1,   2.275,  1.175, 1,   6,  3, 40, 2, 1, 0},
                                                {1, 4.5573,  1,   4.05,   1.232, 1,   6,  3, 54, 4, 1, 0},
                                                {1, 5.0597,  1,   4.455,  1.121, 1,   6,  3, 42, 3, 1, 0},
                                                {1, 3.891,   1,   4.455,  0.988, 1,   6,  3, 56, 2, 1, 0},
                                                {1, 5.898,   1,   5.85,   1.24,  1,   7,  3, 51, 2, 1, 1},
                                                {1, 5.6039,  1,   9.52,   1.501, 0,   6,  3, 32, 1, 1, 0},
                                                {1, 15.4202, 2.5, 9.8,    3.42,  2,   10, 5, 42, 2, 1, 1},
                                                {1, 14.4598, 2.5, 12.8,   3,     2,   9,  5, 14, 4, 1, 1},
                                                {1, 5.8282,  1,   6.435,  1.225, 2,   6,  3, 32, 1, 1, 0},
                                                {1, 5.3003,  1,   4.9883, 1.552, 1,   6,  3, 30, 1, 2, 0},
                                                {1, 6.2712,  1,   5.52,   0.975, 1,   5,  2, 30, 1, 2, 0},
                                                {1, 5.9592,  1,   6.666,  1.121, 2,   6,  3, 32, 2, 1, 0},
                                                {1, 5.05,    1,   5,      1.02,  0,   5,  2, 46, 4, 1, 1},
                                                {1, 5.6039,  1,   9.52,   1.501, 0,   6,  3, 32, 1, 1, 0},
                                                {1, 8.2464,  1.5, 5.15,   1.664, 2,   8,  4, 50, 4, 1, 0},
                                                {1, 6.6969,  1.5, 6.092,  1.488, 1.5, 7,  3, 22, 1, 1, 1},
                                                {1, 7.7841,  1.5, 7.102,  1.376, 1,   6,  3, 17, 2, 1, 0},
                                                {1, 9.0384,  1,   7.8,    1.5,   1.5, 7,  3, 23, 3, 3, 0},
                                                {1, 5.9894,  1,   5.52,   1.256, 2,   6,  3, 40, 4, 1, 1},
                                                {1, 7.5422,  1.5, 4,      1.69,  1,   6,  3, 22, 1, 1, 0},
                                                {1, 8.7951,  1.5, 9.89,   1.82,  2,   8,  4, 50, 1, 1, 1},
                                                {1, 6.0931,  1.5, 6.7265, 1.652, 1,   6,  3, 44, 4, 1, 0},
                                                {1, 8.3607,  1.5, 9.15,   1.777, 2.,  8,  4, 48, 1, 1, 1},
                                                {1, 8.14,    1,   8,      1.504, 2,   7,  3, 3,  1, 3, 0},
                                                {1, 9.1416,  1.5, 7.3262, 1.831, 1.5, 8,  4, 31, 4, 1, 0},
                                                {1, 12,      1.5, 5,      1.2,   2,   6,  3, 30, 3, 1, 1}});
}

Vector b_33() {
    return Vector(
            std::vector<lld>{25.9, 29.5, 27.9, 25.9, 29.9, 29.9, 30.9, 28.9, 84.9, 82.9, 35.9, 31.5, 31.0, 30.9, 30.0,
                             28.9, 36.9, 41.9, 40.5, 43.9, 37.5, 37.9, 44.5, 37.9, 38.9, 36.9, 45.8, 41.0});
}

#define TEST_FUNCTION(A_func, b_func, x_base_func, function) { \
auto A = A_func(); \
auto x = b_func(); \
auto x_base = x_base_func(); \
function(A, x); \
}

#define RUN_EVERY_TEST(group_name, A_func, b_func, x_base_func) \
    TEST_FUNCTION(A_func, b_func, x_base_func, LU_Solve_InPlace) \
    TEST_FUNCTION(A_func, b_func, x_base_func, LU_FP_Solve_InPlace) \
    TEST_FUNCTION(A_func, b_func, x_base_func, LU_PP_Solve_InPlace) \
    TEST_FUNCTION(A_func, b_func, x_base_func, Cholesky_Solve_InPlace) \
    TEST_FUNCTION(A_func, b_func, x_base_func, Cholesky_LDLT_Solve_InPlace) \
    TEST_FUNCTION(A_func, b_func, x_base_func, QR_Solve_InPlace)

TEST_CASE("HW 3.1") {
    RUN_EVERY_TEST(Q1_1, A_1, b_1, x_1)
    RUN_EVERY_TEST(Q1_2, A_2, b_2, x_2)
    RUN_EVERY_TEST(Q1_3, A_3, b_3, x_3)
}

TEST_CASE("HW 3.2") {
    auto t = t_22();

    auto A = Matrix(t.size, 3);
    for (ull i = 0; i < t.size; i++) {
        A.matrix[i][0] = t.array[i] * t.array[i];
        A.matrix[i][1] = t.array[i];
        A.matrix[i][2] = 1;
    }

    auto y = y_22();
    auto x = QR_Solve(A, y);
}

TEST_CASE("HW 3.3") {
    auto y = b_33();
    auto A = A_33();

    auto x = QR_Solve(A, y);
}

