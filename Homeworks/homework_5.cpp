//
// Created by TianKai Ma on 2023/11/30.
//

#include "CustomMath_lib.h"

#define ENABLE_RESULT_PRINTING

#ifdef ENABLE_RESULT_PRINTING
#define PRINT_RESULT(x) x.print();
#else
#define PRINT_RESULT(x)
#endif

lld f(lld x, lld y) {
    return std::sin(x * y);
}

lld phi(lld x, lld y) {
    return x * x + y * y;
}

void par_1() {
    std::cout << "------ Q 5.1 ------" << std::endl;

    auto n = 20;
    auto h = 1.0 / n;
    auto A = Matrix(n * n, n * n);
    auto b = Vector(n * n);

    for (ull i = 0; i < n * n; i++) {
        for (ull j = 0; j < n * n; j++) {
            if (i == j) {
                A.matrix[i][j] = 1 + h * h / 4;
            } else if ((i == j + n || i == j - n) || (i == j + 1 && i % n != 0) || (i == j - 1 && j % n != 0)) {
                A.matrix[i][j] = -1.0 / 4;
            }
        }

        b.array[i] = (h * h / 4) * f((lld) (i / n + 1) * h, (lld) (i % n + 1) * h); // NOLINT(*-integer-division)
    }

    for (ull i = 0; i < n; i++) {
        b.array[i] += phi(0, (lld) (i + 1) * h) / 4;
        b.array[n * n - n + i] += phi(1, (lld) (i + 1) * h) / 4;
    }

    for (ull i = 0; i < n; i++) {
        b.array[i * n] += phi((lld) (i + 1) * h, 0) / 4;
        b.array[i * n + n - 1] += phi((lld) (i + 1) * h, 1) / 4;
    }

//    A.print();
//    b.print();

    auto x_default = Vector(n * n, 1);
    auto input = IterationMethodInput{A, b, x_default, 1e-7,};
    auto output = ConjugateGradientMethod(input);
    std::cout << output.iteration_count << " iterations" << std::endl;
    std::cout << output.time_cost.count() << " μs" << std::endl;
    PRINT_RESULT(output.x)
}

void par_2_tries(ull n) {
    auto A = Matrix::hilbert(n);
    auto b = Vector(n);
    for (ull i = 0; i < n; i++) {
        for (ull j = 0; j < n; j++) {
            b.array[i] += A.matrix[i][j];
        }
        b.array[i] /= 3;
    }

    auto x_default = Vector(n, 1);

    auto input = IterationMethodInput{A, b, x_default, 1e-10,};

    std::cout << std::endl << "n = " << n << std::endl;
    auto output = ConjugateGradientMethod(input);
    std::cout << output.iteration_count << " iterations" << std::endl;
    std::cout << output.time_cost.count() << " μs" << std::endl;
    PRINT_RESULT(output.x)
}

void par_2() {
    std::cout << "------ Q 5.2 ------" << std::endl;

    par_2_tries(20);
    par_2_tries(40);
    par_2_tries(60);
    par_2_tries(80);

}

void par_3() {
    std::cout << "------ Q 5.3 ------" << std::endl;

    auto A = Matrix("[10 1 2 3 4;1 9 -1 2 -3;2 -1 7 3 -5;3 2 3 12 -1;4 -3 -5 -1 15]");
    auto b = Vector("[12 -27 14 -17 12]");
    auto x_default = Vector("[1 1 1 1 1]");

    auto input = IterationMethodInput{A, b, x_default, 1e-10,};

    std::cout << std::endl << "Jacobi Iteration:" << std::endl;
    auto output = JacobiIteration(input);
    std::cout << output.iteration_count << " iterations" << std::endl;
    std::cout << output.time_cost.count() << " μs" << std::endl;
    PRINT_RESULT(output.x)

    std::cout << std::endl << "Gauss-Seidel Iteration:" << std::endl;
    output = GaussSeidelIteration(input);
    std::cout << output.iteration_count << " iterations" << std::endl;
    std::cout << output.time_cost.count() << " μs" << std::endl;
    PRINT_RESULT(output.x)

    std::cout << std::endl << "Conjugate Gradient Method:" << std::endl;
    output = ConjugateGradientMethod(input);
    std::cout << output.iteration_count << " iterations" << std::endl;
    std::cout << output.time_cost.count() << " μs" << std::endl;
    PRINT_RESULT(output.x)
}

int homework_5() {
    par_1();
    par_2();
    par_3();

    return 0;
}
