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

#define ENABLE_ITERATION_METHOD_TIMING

#ifdef ENABLE_ITERATION_METHOD_TIMING
#define ITERATION_METHOD_TIMING_START auto start = std::chrono::high_resolution_clock::now();
#define ITERATION_METHOD_TIMING_END auto end = std::chrono::high_resolution_clock::now(); \
                  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
#define ITERATION_METHOD_RETURN_DURATION duration
#else
#define ITERATION_METHOD_TIMING_START
#define ITERATION_METHOD_TIMING_END
#define ITERATION_METHOD_RETURN_DURATION std::chrono::microseconds(0)
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

lld f(lld x, lld y) {
    return x + y;
}

lld g(lld x, lld y) {
    return std::exp(x * y);
}

lld mGet(const Matrix &m, int i, int j) { // terrible naming, but fuck it.
    if (i == -1 || i >= m.rows || j == -1 || j >= m.cols) return 1;
    return m.matrix[i][j];
}

Matrix JacobiIter(const Matrix &old) {
    auto h = 1.0 / old.rows;
    auto newMatrix = Matrix(old.rows, old.cols);
    for (int i = 0; i < old.rows; i++) {
        for (int j = 0; j < old.cols; j++) {
            newMatrix.matrix[i][j] =
                    (mGet(old, i, j - 1) + mGet(old, i - 1, j) +
                     mGet(old, i, j + 1) + mGet(old, i + 1, j) +
                     h * h * f(i * h, j * h)) /
                    (4 + h * h * g(i * h, j * h));
        }
    }
    return newMatrix;
}

Matrix GSIter(const Matrix &old) {
    auto h = 1.0 / old.rows;
    auto newMatrix = Matrix(old.rows, old.cols);
    for (int i = 0; i < old.rows; i++) {
        for (int j = 0; j < old.cols; j++) {
            newMatrix.matrix[i][j] =
                    (mGet(newMatrix, i, j - 1) + mGet(newMatrix, i - 1, j) +
                     mGet(old, i, j + 1) + mGet(old, i + 1, j) +
                     h * h * f(i * h, j * h)) /
                    (4 + h * h * g(i * h, j * h));
        }
    }
    return newMatrix;
}

Matrix SORIter(const Matrix &old, lld omega) {
    auto h = 1.0 / old.rows;
    auto newMatrix = Matrix(old.rows, old.cols);
    for (int i = 0; i < old.rows; i++) {
        for (int j = 0; j < old.cols; j++) {
            auto tmp = (mGet(newMatrix, i, j - 1) + mGet(newMatrix, i - 1, j) +
                        mGet(old, i, j + 1) + mGet(old, i + 1, j) +
                        h * h * f(i * h, j * h)) /
                       (4 + h * h * g(i * h, j * h));
            newMatrix.matrix[i][j] = old.matrix[i][j] * (1 - omega) + tmp * omega;
        }
    }
    return newMatrix;
}

typedef struct {
    Matrix m;
    int iteration_count;
    std::chrono::microseconds time_cost;
} MatrixIterationMethodOutput;

MatrixIterationMethodOutput MatrixJacobiIteration(int N = 20) {
    auto m = Matrix(N, N, 0);
    auto precision = 1e-7;

    ITERATION_METHOD_TIMING_START

    for (int i = 0; i < ITERATION_METHOD_MAX_ITERATION; i++) {
        auto new_m = JacobiIter(m);
        if ((new_m - m).norm() <= precision) {
            ITERATION_METHOD_TIMING_END

            return {
                    new_m,
                    i,
                    ITERATION_METHOD_RETURN_DURATION
            };
        }
        m = new_m;
    }

    throw std::invalid_argument("MatrixJacobiIteration: iteration count exceeds ITERATION_METHOD_MAX_ITERATION");
}

MatrixIterationMethodOutput MatrixGSIteration(int N = 20) {
    auto m = Matrix(N, N, 0);
    auto precision = 1e-7;

    ITERATION_METHOD_TIMING_START

    for (int i = 0; i < ITERATION_METHOD_MAX_ITERATION; i++) {
        auto new_m = GSIter(m);
        if ((new_m - m).norm() <= precision) {
            ITERATION_METHOD_TIMING_END

            return {
                    new_m,
                    i,
                    ITERATION_METHOD_RETURN_DURATION
            };
        }
        m = new_m;
    }

    throw std::invalid_argument("MatrixGSIteration: iteration count exceeds ITERATION_METHOD_MAX_ITERATION");
}

MatrixIterationMethodOutput MatrixSORIteration(int N = 20, lld omega = 1.8) {
    auto m = Matrix(N, N, 0);
    auto precision = 1e-7;

    ITERATION_METHOD_TIMING_START

    for (int i = 0; i < ITERATION_METHOD_MAX_ITERATION; i++) {
        auto new_m = SORIter(m, omega);
        if ((new_m - m).norm() <= precision) {
            ITERATION_METHOD_TIMING_END

            return {
                    new_m,
                    i,
                    ITERATION_METHOD_RETURN_DURATION
            };
        }
        m = new_m;
    }

    throw std::invalid_argument("MatrixSORIteration: iteration count exceeds ITERATION_METHOD_MAX_ITERATION");
}

void par_2_try(int N = 20) {
    std::cout << std::endl << "N = " << N << std::endl;

    auto m = MatrixJacobiIteration(N);
    std::cout << std::endl << "Jacobi Iteration:" << std::endl;
    std::cout << m.iteration_count << " iterations" << std::endl;
    std::cout << m.time_cost.count() << " μs" << std::endl;
    std::cout << m.m.min() << std::endl;

    m = MatrixGSIteration(N);
    std::cout << std::endl << "Gauss-Seidel Iteration:" << std::endl;
    std::cout << m.iteration_count << " iterations" << std::endl;
    std::cout << m.time_cost.count() << " μs" << std::endl;
    std::cout << m.m.min() << std::endl;

    auto omega = 1.8;
    if (N == 40) omega = 1.9;
    if (N == 60) omega = 1.9;

    m = MatrixSORIteration(N, omega);
    std::cout << std::endl << "SOR Iteration (omega=" << omega << "):" << std::endl;
    std::cout << m.iteration_count << " iterations" << std::endl;
    std::cout << m.time_cost.count() << " μs" << std::endl;
    std::cout << m.m.min() << std::endl;
}

void par_2() {
    std::cout << "------ Q 4.2 ------" << std::endl;
    par_2_try(20);
    par_2_try(40);
    par_2_try(60);
}

int homework_4() {
    par_1();
    par_2();
    return 0;
}