//
// Created by TianKai Ma on 2023/11/30.
//

#include "homework_5.h"

#define ENABLE_RESULT_PRINTING
#define ENABLE_ITERATION_METHOD_TIMING

#ifdef ENABLE_RESULT_PRINTING
#define PRINT_RESULT(x) x.print();
#else
#define PRINT_RESULT(x)
#endif

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

void par_2_tries(ull n) {
    auto A = Matrix::hilbert(n);
    auto b = Vector(n);
    for (ull i = 0; i < n; i++) {
        for (ull j = 0; j<n; j++) {
            b.array[i] += A.matrix[i][j];
        }
        b.array[i]/=3;
    }

    auto x_default = Vector(n, 1);

    auto input = IterationMethodInput {
        A,
        b,
        x_default,
        1e-10,
    };

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

    auto input = IterationMethodInput {
        A,
        b,
        x_default,
        1e-10,
    };

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
    par_2();
    par_3();

    return 0;
}
