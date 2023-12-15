//
// Created by tiankaima on 23-10-24.
//

#include "homework_2.h"

void homework_2_par_1() {
#ifdef DEBUG
    std::cout << "hilbert_norm_inf = [" << std::endl;
#else
    std::cout << "------ Q 2.1 ------" << std::endl;
#endif

    for (int i = 5; i <= 20; i++) {
        Matrix m = Matrix::hilbert(i);
        // this is unnecessary since hilbert matrix is symmetric
        // m = m.transpose();
        lld condition_number = MatrixNorm_1(m) * MatrixNorm_A_Inv_T_1(m);
        std::cout << std::setprecision(std::numeric_limits<lld>::digits10 + 1);

#ifdef DEBUG
        // print as pairs of (n, condition_number) for plotting
        std::cout << "(" << i << ", " << condition_number << ")," << std::endl;
#else
        std::cout << "n = " << i << ", condition_number = " << condition_number << std::endl;
#endif

    }

#ifdef DEBUG
    std::cout << std::endl << "]" << std::endl;
#endif
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

#ifdef DEBUG
    std::cout << "(" << n << ", " << real_diff << ", " << rho << ")," << std::endl;
#else
    std::cout << "n = " << n << std::endl;
    std::cout << std::setprecision(std::numeric_limits<lld>::digits10 + 1);
    std::cout << "real diff = " << real_diff << std::endl;
    std::cout << "calculated diff = " << rho << std::endl;
    std::cout << "diff in diff = " << rho - real_diff << std::endl;
#endif
}

void homework_2_par_2() {
#ifdef DEBUG
    std::cout << "diff_inspection = [" << std::endl;
    for (int n = 0; n < 100; n++) {
        for (int i = 5; i <= 30; i++) {
            diff_inspection(i);
        }
    }
    std::cout << "]" << std::endl;
#else
    std::cout << "------ Q 2.2 ------" << std::endl;

    for (int i = 5; i <= 30; i++) {
        diff_inspection(i);
    }
#endif
}

int homework_2() {
    homework_2_par_1();
    homework_2_par_2();
    return 0;
}