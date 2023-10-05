//
// Created by tiankaima on 23-10-5.
//

#include "homework_1.h"

/*
 * 1.1.1
 *
 * Test Case:
 * A = [1 0 0; 5 -8 0; -2 -6 -1]
 * b = [8 8 8]
 * x = [8 4 -48]
 */
void homework_1_1_1() {
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
void homework_1_1_2() {
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
void homework_1_1_3() {
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
void homework_1_2_1() {
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
void homework_1_2_2() {
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

int homework_1() {
    homework_1_1_1();
    homework_1_1_2();
    homework_1_1_3();
    homework_1_2_1();
    homework_1_2_2();

    return 0;
}