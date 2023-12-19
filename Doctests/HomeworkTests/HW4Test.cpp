//
// Created by tiankaima on 23-12-16.
//

#include "CustomMath_lib.h"
#include "../doctest.h"

Matrix A_1(double eps, double a, int n, double h) {
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

Vector x_default_1(double eps, double a, int n, double h) {
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

void par_1_try(double eps = 0.1) {
    auto a = 0.5;
    auto n = 100;
    auto h = 1.0 / n;

    auto A = A_1(eps, a, n, h);
    auto b = b_1(eps, a, n, h);
    auto x_default = x_default_1(eps, a, n, h);

    auto input = IterationMethodInput{A, b, x_default, 1e-6};

    auto x_real_value = x_real_value_1(eps, a, n, h);

    auto output = JacobiIteration(input);
    output = GaussSeidelIteration(input);

    auto omega = 1.6;
    if (eps == 0.1) omega = 1.5;
    if (eps == 0.01) omega = 1.4;
    if (eps == 0.0001) omega = 1;
    output = SORIteration(input, omega);
}

TEST_CASE("HW 4.1") {
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
    auto h = 1.0 / (lld) old.rows;
    auto newMatrix = Matrix(old.rows, old.cols);
    for (int i = 0; i < old.rows; i++) {
        for (int j = 0; j < old.cols; j++) {
            newMatrix.matrix[i][j] =
                    (mGet(old, i, j - 1) + mGet(old, i - 1, j) + mGet(old, i, j + 1) + mGet(old, i + 1, j) +
                     h * h * f(i * h, j * h)) / (4 + h * h * g(i * h, j * h));
        }
    }
    return newMatrix;
}

Matrix GSIter(const Matrix &old) {
    auto h = 1.0 / (lld) old.rows;
    auto newMatrix = Matrix(old.rows, old.cols);
    for (int i = 0; i < old.rows; i++) {
        for (int j = 0; j < old.cols; j++) {
            newMatrix.matrix[i][j] =
                    (mGet(newMatrix, i, j - 1) + mGet(newMatrix, i - 1, j) + mGet(old, i, j + 1) + mGet(old, i + 1, j) +
                     h * h * f(i * h, j * h)) / (4 + h * h * g(i * h, j * h));
        }
    }
    return newMatrix;
}

Matrix SORIter(const Matrix &old, lld omega) {
    auto h = 1.0 / (lld) old.rows;
    auto newMatrix = Matrix(old.rows, old.cols);
    for (int i = 0; i < old.rows; i++) {
        for (int j = 0; j < old.cols; j++) {
            auto tmp =
                    (mGet(newMatrix, i, j - 1) + mGet(newMatrix, i - 1, j) + mGet(old, i, j + 1) + mGet(old, i + 1, j) +
                     h * h * f(i * h, j * h)) / (4 + h * h * g(i * h, j * h));
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

    for (int i = 0; i < ITERATION_METHOD_MAX_ITERATION; i++) {
        auto new_m = JacobiIter(m);
        if ((new_m - m).norm() <= precision) {

            return {new_m, i, std::chrono::microseconds(0)};
        }
        m = new_m;
    }

    throw std::invalid_argument("MatrixJacobiIteration: iteration count exceeds ITERATION_METHOD_MAX_ITERATION");
}

MatrixIterationMethodOutput MatrixGSIteration(int N = 20) {
    auto m = Matrix(N, N, 0);
    auto precision = 1e-7;

    for (int i = 0; i < ITERATION_METHOD_MAX_ITERATION; i++) {
        auto new_m = GSIter(m);
        if ((new_m - m).norm() <= precision) {
            return {new_m, i, std::chrono::microseconds(0)};
        }
        m = new_m;
    }

    throw std::invalid_argument("MatrixGSIteration: iteration count exceeds ITERATION_METHOD_MAX_ITERATION");
}

MatrixIterationMethodOutput MatrixSORIteration(int N = 20, lld omega = 1.8) {
    auto m = Matrix(N, N, 0);
    auto precision = 1e-7;

    for (int i = 0; i < ITERATION_METHOD_MAX_ITERATION; i++) {
        auto new_m = SORIter(m, omega);
        if ((new_m - m).norm() <= precision) {

            return {new_m, i, std::chrono::microseconds(0)};
        }
        m = new_m;
    }

    throw std::invalid_argument("MatrixSORIteration: iteration count exceeds ITERATION_METHOD_MAX_ITERATION");
}

void par_2_try(int N = 20) {
    auto m = MatrixJacobiIteration(N);
    m = MatrixGSIteration(N);

    auto omega = 1.8;
    if (N == 40) omega = 1.9;
    if (N == 60) omega = 1.9;

    m = MatrixSORIteration(N, omega);
}

TEST_CASE("HW 4.2") {
    par_2_try(20);
    par_2_try(40);
    par_2_try(60);
}