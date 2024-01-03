#include "includes/NLAMethods.h"

// homework 8 (SVD):
int main() {
    auto A = Matrix(8, 5, 1, 10);
    A = BidiagonalizationMethod(A).B;
    A.matrix[1][0] = 5;

    A.print();

    auto r = WilkinsonShiftIteration(A);

    r.B.print();
    (r.P * A * r.Q).print();

    return 0;
}