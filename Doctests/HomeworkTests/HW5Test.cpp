//
// Created by tiankaima on 23-12-16.
//

#include "CustomMath_lib.h"
#include "../doctest.h"

lld f6(lld x, lld y) {
    return std::sin(x * y);
}

lld phi(lld x, lld y) {
    return x * x + y * y;
}

TEST_CASE("HW 5.1") {
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

        b.array[i] = (h * h / 4) * f6((lld) (i / n + 1) * h, (lld) (i % n + 1) * h); // NOLINT(*-integer-division)
    }

    for (ull i = 0; i < n; i++) {
        b.array[i] += phi(0, (lld) (i + 1) * h) / 4;
        b.array[n * n - n + i] += phi(1, (lld) (i + 1) * h) / 4;
    }

    for (ull i = 0; i < n; i++) {
        b.array[i * n] += phi((lld) (i + 1) * h, 0) / 4;
        b.array[i * n + n - 1] += phi((lld) (i + 1) * h, 1) / 4;
    }

    auto x_default = Vector(n * n, 1);
    auto input = IterationMethodInput{A, b, x_default, 1e-7,};
    auto output = ConjugateGradientMethod(input);
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
    auto output = ConjugateGradientMethod(input);
}

TEST_CASE("HW 5.2") {
    par_2_tries(20);
    par_2_tries(40);
    par_2_tries(60);
    par_2_tries(80);
}

TEST_CASE("HW 5.3") {
    auto A = Matrix("[10 1 2 3 4;1 9 -1 2 -3;2 -1 7 3 -5;3 2 3 12 -1;4 -3 -5 -1 15]");
    auto b = Vector("[12 -27 14 -17 12]");
    auto x_default = Vector("[1 1 1 1 1]");

    auto input = IterationMethodInput{A, b, x_default, 1e-10,};
    auto output = JacobiIteration(input);
    output = GaussSeidelIteration(input);
    output = ConjugateGradientMethod(input);
}
