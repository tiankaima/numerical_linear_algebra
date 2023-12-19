//
// Created by tiankaima on 23-10-5.
//

#include "CustomMath_lib.h"
#include "../doctest.h"

TEST_CASE("GaussMethod::LowerTriangleMatrix_Solve()") {
    auto A = Matrix("[1 0 0; 5 -8 0; -2 -6 -1]");
    auto b = Vector("[8 8 8]");
    auto expected_x = Vector("[8 4 -48]");

    auto x = LowerTriangleMatrix_Solve(A, b);
    CHECK_EQ(x, expected_x);
}

TEST_CASE("GaussMethod::UpperTriangleMatrix_Solve()") {
    auto A = Matrix("[9 -8 2; 0 -4 10; 0 0 3]");
    auto b = Vector("[2 -8 6]");
    auto expected_x = Vector("[6 7 2]");
    auto x = UpperTriangleMatrix_Solve(A, b);

    CHECK_EQ(x, expected_x);
}

TEST_CASE("GaussMethod::LU_Decomposition()") {
    auto A = Matrix("[-2 10 2; 6 0 4; 4 10 8]");
    auto expected_L = Matrix("[1 0 0; -3 1 0; -2 1 1]");
    auto expected_U = Matrix("[-2 10 2; 0 30 10; 0 0 2]");
    auto [L, U] = LU_Decomposition(A);

    CHECK_EQ(L, expected_L);
    CHECK_EQ(U, expected_U);
}

TEST_CASE("GaussMethod::LU_FP_Decomposition()") {
    auto A = Matrix("[-2 10 2; 6 0 4; 4 10 8]");
    auto [L, U, P, Q] = LU_FP_Decomposition(A);
    auto PAQ = P * A * Q;
    auto LU = L * U;

    CHECK_EQ(PAQ, LU);
}


TEST_CASE("GaussMethod::LU_PP_Decomposition()") {
    auto A = Matrix("[-2 10 2; 6 0 4; 4 10 8]");
    auto [L, U, P] = LU_PP_Decomposition(A);

    Matrix PA = P * A;
    Matrix LU = L * U;

    CHECK_EQ(PA, LU);
}

