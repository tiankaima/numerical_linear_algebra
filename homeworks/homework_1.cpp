//
// Created by tiankaima on 23-10-5.
//

#include <cfloat>
#include "homework_1.h"

/*
 * 1.1.1
 *
 * Test Case:
 * A = [1 0 0; 5 -8 0; -2 -6 -1]
 * b = [8 8 8]
 * x = [8 4 -48]
 */
void algorithm_1_1_1() {
    std::cout << "------ 1.1.1 ------" << std::endl;

    Matrix A;
    Array b, x, expected_x;

    A = Matrix("[1 0 0; 5 -8 0; -2 -6 -1]");
    b = Array("[8 8 8]");
    expected_x = Array("[8 4 -48]");

    x = LowerGaussSolve(A, b);
    std::cout << "x = " << std::endl;
    x.print();

    if (x == expected_x) {
        std::cout << "Test Passed" << std::endl;
    } else {
        std::cout << "Test Failed" << std::endl;
    }
}

/*
 * 1.1.2
 *
 * Test Case:
 * A = [9 -8 2; 0 -4 10; 0 0 3]
 * b = [2 -8 6]
 * x = [6 7 2]
 */
void algorithm_1_1_2() {
    std::cout << "------ 1.1.2 ------" << std::endl;

    Matrix A;
    Array b, x, expected_x;

    A = Matrix("[9 -8 2; 0 -4 10; 0 0 3]");
    b = Array("[2 -8 6]");
    expected_x = Array("[6 7 2]");

    x = UpperGaussSolve(A, b);
    std::cout << "x = " << std::endl;
    x.print();

    if (x == expected_x) {
        std::cout << "Test Passed" << std::endl;
    } else {
        std::cout << "Test Failed" << std::endl;
    }
}

/*
 * 1.1.3
 *
 * Test Case:
 * A = [-2 10 2; 6 0 4; 4 10 8]
 * L = [1 0 0; -3 1 0; -2 1 1]
 * U = [-2 10 2; 0 30 10; 0 0 2]
 */
void algorithm_1_1_3() {
    std::cout << "------ 1.1.3 ------" << std::endl;

    Matrix A, L, U, expected_L, expected_U;
    A = Matrix("[-2 10 2; 6 0 4; 4 10 8]");
    expected_L = Matrix("[1 0 0; -3 1 0; -2 1 1]");
    expected_U = Matrix("[-2 10 2; 0 30 10; 0 0 2]");

    LU_Factorization(A, &L, &U);
    std::cout << "L = " << std::endl;
    L.print();
    std::cout << "U = " << std::endl;
    U.print();

    if (L == expected_L && U == expected_U) {
        std::cout << "Test Passed" << std::endl;
    } else {
        std::cout << "Test Failed" << std::endl;
    }
}

/*
 * 1.2.1
 *
 * Reusing code & test case from 1.1.3
 */
void algorithm_1_2_1() {
    std::cout << "------ 1.2.1 ------" << std::endl;

    Matrix A, L, U, P, Q;
    A = Matrix("[-2 10 2; 6 0 4; 4 10 8]");

    LU_FP_Factorization(A, &L, &U, &P, &Q);

    std::cout << "Verify that PAQ = LU" << std::endl;
    Matrix PAQ = P * A * Q;
    Matrix LU = L * U;
    std::cout << "PAQ = " << std::endl;
    PAQ.print();
    std::cout << "LU = " << std::endl;
    LU.print();

    if (PAQ == LU) {
        std::cout << "Test Passed" << std::endl;
    } else {
        std::cout << "Test Failed" << std::endl;
    }
}

/*
 * 1.2.2
 *
 * Reusing code & test case from 1.2.1, this time we only use P
 */
void algorithm_1_2_2() {
    std::cout << "------ 1.2.2 ------" << std::endl;

    Matrix A, L, U, P;

    A = Matrix("[-2 10 2; 6 0 4; 4 10 8]");
    LU_PP_Factorization(A, &L, &U, &P);

    std::cout << "Verify that PA = LU" << std::endl;
    Matrix PA = P * A;
    Matrix LU = L * U;
    std::cout << "PA = " << std::endl;
    PA.print();
    std::cout << "LU = " << std::endl;
    LU.print();

    if (PA == LU) {
        std::cout << "Test Passed" << std::endl;
    } else {
        std::cout << "Test Failed" << std::endl;
    }
}

/*
 * 1.3.1
 *
 * Test Case:
 * A = [155 -123 -67; -123 141 -20; -67 -20 153]
 */
void algorithm_1_3_1() {
    std::cout << "------ 1.3.1 ------" << std::endl;

    Matrix A, L;
    A = Matrix("[155 -123 -67; -123 141 -20; -67 -20 153]");

    CholeskyFactorization(A, &L);
    std::cout << "L = " << std::endl;
    L.print();

    Matrix LLT = L * L.transpose();
    LLT.print();
    A.print();

    if (LLT == A) {
        std::cout << "Test Passed" << std::endl;
    } else {
        std::cout << "Test Failed" << std::endl;
    }
}

/*
 * 1.3.2
 *
 * Test Case:
 * A = [155 -123 -67; -123 141 -20; -67 -20 153]
 */
void algorithm_1_3_2() {
    std::cout << "------ 1.3.2 ------" << std::endl;

    Matrix A, L, D;
    A = Matrix("[155 -123 -67; -123 141 -20; -67 -20 153]");

    Cholesky_LDLT_Factorization(A, &L, &D);
    std::cout << "L = " << std::endl;
    L.print();
    std::cout << "D = " << std::endl;
    D.print();

    Matrix LDLT = L * D * L.transpose();
    LDLT.print();
    A.print();

    if (LDLT == A) {
        std::cout << "Test Passed" << std::endl;
    } else {
        std::cout << "Test Failed" << std::endl;
    }
}

void homework_1_par_1() {
    std::cout << "------ Q 1.1 ------" << std::endl;

    int n = 84;
    Matrix A, L, U, P, Q;
    Array b, x, y, x_base;

    A = Matrix(n, n);
    for (int i = 0; i < n; i++) {
        A.matrix[i][i] = 6;
        if (i < n - 1) {
            A.matrix[i][i + 1] = 1;
            A.matrix[i + 1][i] = 8;
        }
    }

    b = Array(n);
    for (int i = 1; i < n - 1; i++) {
        b.array[i] = 15;
    }
    b.array[0] = 7;
    b.array[n - 1] = 14;

    x_base = Array(n);
    for (int i = 0; i < n; i++) {
        x_base.array[i] = 1;
    }

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Method 1 aka 1.1.3
    LU_Factorization(A, &L, &U);
    y = LowerGaussSolve(L, b);
    x = UpperGaussSolve(U, y);

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Method 1" << std::endl;
    x.print();
    std::cout << "diff = " << (x - x_base).norm() << std::endl;
    std::cout << "time = " << duration.count() << " microseconds" << std::endl;

    // Method 2 aka 1.2.1
    LU_FP_Factorization(A, &L, &U, &P, &Q);
    Array Pb = P * b;
    Array UQix = LowerGaussSolve(L, Pb);
    Array Qix = UpperGaussSolve(U, UQix);
    x = Q * Qix;

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Method 2" << std::endl;
    x.print();
    std::cout << "diff = " << (x - x_base).norm() << std::endl;
    std::cout << "time = " << duration.count() << " microseconds" << std::endl;

    // Method 3 aka 1.2.2
    LU_PP_Factorization(A, &L, &U, &P);
    Pb = P * b;
    y = LowerGaussSolve(L, Pb);
    x = UpperGaussSolve(U, y);

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Method 3" << std::endl;
    x.print();
    std::cout << "diff = " << (x - x_base).norm() << std::endl;
    std::cout << "time = " << duration.count() << " microseconds" << std::endl;
}

void homework_1_par_2() {
    std::cout << "------ Q 1.2 ------" << std::endl;

    Matrix A;
    Array b;

    A = Matrix(100, 100);
    for (int i = 0; i < 100; i++) {
        A.matrix[i][i] = 10;
        if (i < 99) {
            A.matrix[i][i + 1] = 1;
            A.matrix[i + 1][i] = 1;
        }
    }
    b = Array(100);
    for (int i = 0; i < 100; i++) {
        b.array[i] = 1;
    }

    Matrix L;
    auto start = std::chrono::high_resolution_clock::now();
    CholeskyFactorization(A, &L);
    Array y = LowerGaussSolve(L, b);
    Array x = UpperGaussSolve(L.transpose(), y);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    x.print();
    std::cout << "time = " << duration.count() << " microseconds" << std::endl;

    Matrix D;
    start = std::chrono::high_resolution_clock::now();
    Cholesky_LDLT_Factorization(A, &L, &D);
    y = LowerGaussSolve(L, b);
    for (int i = 0; i < 100; i++) {
        y.array[i] /= D.matrix[i][i];
    }
    x = UpperGaussSolve(L.transpose(), y);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    x.print();
    std::cout << "time = " << duration.count() << " microseconds" << std::endl;
}

void homework_1_par_3() {
    std::cout << "------ Q 1.3 ------" << std::endl;

    int n = 40;
    Matrix A;
    Array b;

    A = Matrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A.matrix[i][j] = 1.0 / (i + j + 1);
        }
    }
    b = Array(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            b.array[i] += A.matrix[i][j];
        }
    }


    Matrix L;
    auto start = std::chrono::high_resolution_clock::now();
    CholeskyFactorization(A, &L);
    Array y = LowerGaussSolve(L, b);
    Array x = UpperGaussSolve(L.transpose(), y);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    x.print();
    std::cout << "time = " << duration.count() << " microseconds" << std::endl;

    Matrix D;
    start = std::chrono::high_resolution_clock::now();
    Cholesky_LDLT_Factorization(A, &L, &D);
    y = LowerGaussSolve(L, b);
    for (int i = 0; i < n; i++) {
        y.array[i] /= D.matrix[i][i];
    }
    x = UpperGaussSolve(L.transpose(), y);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    x.print();
    std::cout << "time = " << duration.count() << " microseconds" << std::endl;
}

int homework_1() {
    homework_1_par_1();
    homework_1_par_2();
    homework_1_par_3();
}