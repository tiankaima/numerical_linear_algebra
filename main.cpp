#include "includes/NLAMethods.h"

Matrix A_7_1(int n) {
    auto A = Matrix(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                A.matrix[i][j] = 4;
            }
            if (i == j + 1 || i == j - 1) {
                A.matrix[i][j] = 1;
            }
        }
    }
    return A;
}

Matrix A_7_2(int n) {
    auto A = Matrix(n, n);
    for (ull i = 0; i < n; i++) {
        for (ull j = 0; j < n; j++) {
            if (i == j) {
                A.matrix[i][j] = 2;
            } else if (i == j + 1 || i == j - 1) {
                A.matrix[i][j] = -1;
            }
        }
    }

    return A;
}

void part_1() {
    for (auto n: {50, 60, 70, 80, 90, 100}) {
        std::cout << "n = " << n << std::endl;

        auto A = A_7_1(n);
        auto r = JacobiMethod(A, JACOBI_METHOD_TYPE_THRESHOLD);

        r.result.A.clean(1e-8).print();
        r.result.P.print();

        std::cout << "Iteration count: " << r.iteration_count << std::endl;
        std::cout << "Time cost: " << r.time_cost.count() << std::endl;
    }
}

void part_2() {
    auto n = 100;
    auto x = Vector(n, 2);
    auto y = Vector(n - 1, -1);
    auto A = A_7_2(n);


    auto I = Matrix::identity(n);
    auto x_default = Vector(n, 1);
    auto r = BisectMethod(x, y);

    for (auto &lambda: r.array) {
        auto B = A - I * lambda;
        auto input = PowerIterationInput{B, x_default, 1000,};
        auto k = RevPowerIteration(input);
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "lambda = " << lambda << "\t :";
        k.result.print();
    }
}

// homework 7:
int main() {
    part_1();
    part_2();
    return 0;
}