#include "CustomMath_lib.h"

int main() {
    auto m = Matrix("[5 1 -2; 1 2 0; -2 0 -10]");
    auto I = Matrix::identity(m.rows);
    auto lambda = -10.263471;
    auto A = m - I * lambda;
    auto x = Vector("[1 1 1]");

    auto result = RevPowerIteration(PowerIterationInput{A, x, 1000});

    std::cout << "Eigenvector: " << std::endl;
    result.result.print();

    return 0;
}