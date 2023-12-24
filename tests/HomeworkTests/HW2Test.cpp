//
// Created by tiankaima on 23-12-16.
//

#include "../../includes/NLAMethods.h"
#include "../doctest.h"

TEST_CASE("HW 2.1") {
    for (int i = 5; i <= 20; i++) {
        Matrix m = Matrix::hilbert(i);
        lld condition_number = MatrixNorm_1(m) * MatrixNorm_A_Inv_T_1(m);
    }
}

void diff_inspection(int n) {
    Matrix A = Matrix::LowerTriangular(n, -1) + Matrix::Diagonal(n, 2);
    for (ull i = 0; i < n; i++) {
        A.matrix[i][n - 1] = 1;
    }
    Vector x = Vector(n, 0, 1);
    Vector b = A * x;
    Vector x_sharp = LU_PP_Solve(A, b);

    // real diff:
    lld real_diff = (x - x_sharp).norm();

    // calculated diff:
    lld v_p = MatrixNorm_A_Inv_T_1(A);
    lld r_p = (b - A * x_sharp).norm();
    lld b_p = VectorNorm_Infinity(b);
    lld mu_p = MatrixNorm_1(A.transpose());

    lld rho = v_p * mu_p * r_p / b_p;
}

TEST_CASE("HW 2.2") {
    for (int n = 0; n < 100; n++) {
        for (int i = 5; i <= 30; i++) {
            diff_inspection(i);
        }
    }
}