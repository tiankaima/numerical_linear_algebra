//
// Created by tiankaima on 23-10-24.
//

#include "homework_2.h"

int homework_2() {
    Matrix m = Matrix(3, 3, 0, 1);
    lld max = MatrixNorm_Infinity(m);
    std::cout << max << std::endl;

    lld max_approx = MatrixNorm_1(m.transpose());
    std::cout << max_approx << std::endl;
    return 0;
}