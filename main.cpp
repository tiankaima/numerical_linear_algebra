#include "CustomMath_lib.h"

int main() {
    auto n = 3;
    auto x = Vector(n, 2);
    auto y = Vector(n - 1, -1);

    auto A = Matrix(n, n);
    for(ull i = 0; i < n; i++) {
        for(ull j = 0; j < n; j++) {
            if(i == j) {
                A.matrix[i][j] = 2;
            } else if(i == j + 1 || i == j - 1) {
                A.matrix[i][j] = -1;
            }
        }
    }
    auto I = Matrix::identity(n);
    auto x_default = Vector(n, 1);

//    for (lld k = -4.0; k <= 4.0; k += 0.1) {
//        auto r = CalculateSignChange(x, y, k);
//        std::cout << k << " " << r << std::endl;
//    }

    auto r = BisectMethod(x, y);
    r.print();

    for (auto &lambda: r.array) {
        auto B = A - I * lambda;
        auto input = PowerIterationInput{B, x_default, 1000,};
        auto k = RevPowerIteration(input);
        k.result.print();
        (B * k.result).print();
    }

    return 0;
}