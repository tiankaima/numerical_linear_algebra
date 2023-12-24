//
// Created by tiankaima on 23-10-5.
//

#include "../includes/NLAMethods.h"

#define TEST_START auto start = std::chrono::high_resolution_clock::now();
#define TEST_END auto end = std::chrono::high_resolution_clock::now(); \
                 auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); \
                 std::cout << "time = " << duration.count() << " microseconds" << std::endl;

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

void homework_1_par_1() {
    std::cout << "------ Q 1.1 ------" << std::endl;

    Matrix A;
    Vector b, x, x_base;

    A = m_1_1();

    b = Vector(84);
    for (int i = 1; i < 84 - 1; i++) {
        b.array[i] = 15;
    }
    b.array[0] = 7;
    b.array[84 - 1] = 14;

    x_base = Vector(84);
    for (int i = 0; i < 84; i++) {
        x_base.array[i] = 1;
    }

    {// 1.1.3
        TEST_START
        x = LU_Solve(A, b);
        TEST_END
        x.print();
        std::cout << "diff = " << (x - x_base).norm() << std::endl;
    }

    {// 1.2.1
        TEST_START
        x = LU_FP_Solve(A, b);
        TEST_END
        x.print();
        std::cout << "diff = " << (x - x_base).norm() << std::endl;
    }

    {// 1.2.2
        TEST_START
        x = LU_PP_Solve(A, b);
        TEST_END
        x.print();
        std::cout << "diff = " << (x - x_base).norm() << std::endl;
    }
}

void homework_1_par_2_1() {
    std::cout << "------ Q 1.2(1) ------" << std::endl;

    Matrix A;
    Vector b, x;

    A = m_1_2_1();
    b = Vector(100);
    for (int i = 0; i < 100; i++) {
        b.array[i] = 1;
    }

    {// 1.3.1
        TEST_START
        x = Cholesky_Solve(A, b);
        TEST_END
        x.print();
    }

    {// 1.3.2
        TEST_START
        x = Cholesky_LDLT_Solve(A, b);
        TEST_END
        x.print();
    }
}

void homework_1_par_2_2() {
    std::cout << "------ Q 1.2(2) ------" << std::endl;

    Matrix A;
    Vector b, x;

    A = m_1_2_2();
    b = Vector(40);
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            b.array[i] += A.matrix[i][j];
        }
    }

    {// 1.3.1
        TEST_START
        x = Cholesky_Solve(A, b);
        TEST_END
        x.print();
    }

    {// 1.3.2
        TEST_START
        x = Cholesky_LDLT_Solve(A, b);
        TEST_END
        x.print();
    }
}

void homework_1_par_3_1() {
    std::cout << "------ Q 1.3: 1.2(1) ------" << std::endl;

    Matrix A;
    Vector b, x;

    A = m_1_2_1();

    b = Vector(100);
    for (int i = 0; i < 100; i++) {
        b.array[i] = 1;
    }

    {
        TEST_START
        x = LU_Solve(A, b);
        TEST_END
        x.print();
    }

    {
        TEST_START
        x = LU_FP_Solve(A, b);
        TEST_END
        x.print();
    }

    {
        TEST_START
        x = LU_PP_Solve(A, b);
        TEST_END
        x.print();
    }

    {
        TEST_START
        x = Cholesky_Solve(A, b);
        TEST_END
        x.print();
    }

    {
        TEST_START
        x = Cholesky_LDLT_Solve(A, b);
        TEST_END
        x.print();
    }
}

void homework_1_par_3_2() {
    std::cout << "------ Q 1.3: 1.2(2) ------" << std::endl;
    Matrix A;
    Vector b, x;

    A = m_1_2_2();

    b = Vector(40);
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++)
            b.array[i] += A.matrix[i][j];
    }

    {
        TEST_START
        x = LU_Solve(A, b);
        TEST_END
        x.print();
    }

    {
        TEST_START
        x = LU_FP_Solve(A, b);
        TEST_END
        x.print();
    }

    {
        TEST_START
        x = LU_PP_Solve(A, b);
        TEST_END
        x.print();
    }

    {
        TEST_START
        x = Cholesky_Solve(A, b);
        TEST_END
        x.print();
    }

    {
        TEST_START
        x = Cholesky_LDLT_Solve(A, b);
        TEST_END
        x.print();
    }
}

int homework_1() {
    homework_1_par_1();
    homework_1_par_2_1();
    homework_1_par_2_2();
    homework_1_par_3_1();
    homework_1_par_3_2();
    return 0;
}