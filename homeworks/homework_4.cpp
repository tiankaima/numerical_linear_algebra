//
// Created by TianKai Ma on 2023/11/23.
//

#include "homework_4.h"

//#define ENABLE_RESULT_PRINTING

#ifdef ENABLE_RESULT_PRINTING
#define PRINT_RESULT(x) x.print();
#else
#define PRINT_RESULT(x)
#endif

Matrix A_1(double eps, [[maybe_unused]] double a, int n, double h) {
    auto A = Matrix(n - 1, n - 1);
    for (ull i = 0; i < n - 1; i++) {
        for (ull j = 0; j < n - 1; j++) {
            if (i == j) {
                A.matrix[i][j] = -(2.0 * eps + h);
            } else if (i == j + 1) {
                A.matrix[i][j] = eps;
            } else if (i == j - 1) {
                A.matrix[i][j] = eps + h;
            }
        }
    }
    return A;
}

Vector b_1(double eps, double a, int n, double h) {
    auto b = Vector(n - 1, a * h * h);

    b.array[0] -= eps * 0;
    b.array[n - 2] -= (eps + h) * 1;

    return b;
}

Vector x_default_1([[maybe_unused]] double eps, [[maybe_unused]] double a, int n, double h) {
    auto x_default = Vector(n - 1, 0);
    for (int i = 0; i < n - 1; i++) {
        x_default.array[i] = i * h;
    }
    return x_default;
}

lld calc(double eps, double a, double x) {
    // y = (1 - a)/(1 - exp(-1/eps)) * (1 - exp(-x/eps)) + a * x
    return (1 - a) / (1 - std::exp(-1 / eps)) * (1 - std::exp(-x / eps)) + a * x;
}

Vector x_real_value_1(double eps, double a, int n, double h) {
    auto x_real_value = Vector(n - 1, 0);
    for (int i = 0; i < n - 1; i++) {
        x_real_value.array[i] = calc(eps, a, i * h);
    }
    return x_real_value;
}

[[maybe_unused]] void best_omega_try() {
    auto eps = 0.0001;
    auto a = 0.5;
    auto n = 100;
    auto h = 1.0 / n;

    auto input = IterationMethodInput{
            A_1(eps, a, n, h),
            b_1(eps, a, n, h),
            x_default_1(eps, a, n, h),
            1e-6
    };

    for (lld omega = 0.1; omega < 2; omega += 0.1) { // NOLINT(*-flp30-c)
        try {
            auto output = SORIteration(input, omega);
            std::cout << "[omega = " << omega << "]: " << output.iteration_count << " iterations" << std::endl;
        } catch (std::exception &e) {
            std::cout << "[omega = " << omega << "]: " << e.what() << std::endl;
        }
    }
}

void par_1_try(double eps = 0.1) {
    std::cout << std::endl << "eps = " << eps << std::endl;

    auto a = 0.5;
    auto n = 100;
    auto h = 1.0 / n;

    auto input = IterationMethodInput{
            A_1(eps, a, n, h),
            b_1(eps, a, n, h),
            x_default_1(eps, a, n, h),
            1e-6
    };

    auto x_real_value = x_real_value_1(eps, a, n, h);
    PRINT_RESULT(x_real_value)

    std::cout << std::endl << "Jacobi Iteration:" << std::endl;
    auto output = JacobiIteration(input);
    std::cout << output.iteration_count << " iterations" << std::endl;
    std::cout << output.time_cost.count() << " μs" << std::endl;
    std::cout << "diff = " << (x_real_value - output.x).norm() << std::endl;

    PRINT_RESULT(output.x)

    std::cout << std::endl << "Gauss-Seidel Iteration:" << std::endl;
    output = GaussSeidelIteration(input);
    std::cout << output.iteration_count << " iterations" << std::endl;
    std::cout << output.time_cost.count() << " μs" << std::endl;
    std::cout << "diff = " << (x_real_value - output.x).norm() << std::endl;
    PRINT_RESULT(output.x)

    auto omega = 1.6;
    if (eps == 0.1) omega = 1.5;
    if (eps == 0.01) omega = 1.4;
    if (eps == 0.0001) omega = 1;

    std::cout << std::endl << "SOR Iteration (omega = " << omega << "):" << std::endl;
    output = SORIteration(input, omega);
    std::cout << output.iteration_count << " iterations" << std::endl;
    std::cout << output.time_cost.count() << " μs" << std::endl;
    std::cout << "diff = " << (x_real_value - output.x).norm() << std::endl;
    PRINT_RESULT(output.x)
}

void par_1() {
    std::cout << "------ Q 4.1 ------" << std::endl;
    par_1_try(1);
    par_1_try(0.1);
    par_1_try(0.01);
    par_1_try(0.0001);
}

int homework_4() {
//    best_omega_try();
    par_1();
    return 0;
}