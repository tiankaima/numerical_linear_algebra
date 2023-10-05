//
// Created by tiankaima on 23-10-5.
//

#include "iostream"
#include "Matrix.h"
#include "Array.h"
#include "GaussMethod.h"
#include "doctest.h"

TEST_CASE("GaussMethod::LowerGaussSolve()") {
    Matrix A;
    Array b, x, expected_x;

    A = Matrix("[1 0 0; 5 -8 0; -2 -6 -1]");
    b = Array("[8 8 8]");
    expected_x = Array("[8 4 -48]");

    x = LowerGaussSolve(A, b);
    CHECK_EQ(x, expected_x);
}

TEST_CASE("GaussMethod::UpperGaussSolve()") {
    Matrix A;
    Array b, x, expected_x;

    A = Matrix("[9 -8 2; 0 -4 10; 0 0 3]");
    b = Array("[2 -8 6]");
    expected_x = Array("[6 7 2]");

    x = UpperGaussSolve(A, b);
    CHECK_EQ(x, expected_x);
}

TEST_CASE("GaussMethod::LU_Factorization()") {
    Matrix A, L, U, expected_L, expected_U;
    A = Matrix("[-2 10 2; 6 0 4; 4 10 8]");
    expected_L = Matrix("[1 0 0; -3 1 0; -2 1 1]");
    expected_U = Matrix("[-2 10 2; 0 30 10; 0 0 2]");

    LU_Factorization(A, &L, &U);

    CHECK_EQ(L, expected_L);
    CHECK_EQ(U, expected_U);
}

TEST_CASE("GaussMethod::LU_FP_Factorization()") {
    Matrix A, L, U, P, Q;
    A = Matrix("[-2 10 2; 6 0 4; 4 10 8]");

    LU_FP_Factorization(A, &L, &U, &P, &Q);

    Matrix PAQ = P * A * Q;
    Matrix LU = L * U;

    CHECK_EQ(PAQ, LU);
}


TEST_CASE("GaussMethod::LU_PP_Factorization()") {
    Matrix A, L, U, P;

    A = Matrix("[-2 10 2; 6 0 4; 4 10 8]");
    LU_PP_Factorization(A, &L, &U, &P);

    Matrix PA = P * A;
    Matrix LU = L * U;

    CHECK_EQ(PA, LU);
}

