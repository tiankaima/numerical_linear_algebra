#include "includes/NLAMethods.h"

// homework 8 (SVD):
int main() {
    auto A = Matrix(8, 5, 1, 10);
    A = BidiagonalizationMethod(A).B;
    A.matrix[1][1] = 0;

    auto r = ReformBidiagonalization(A, 1);

    r.B.print();
    r.G.print();

    return 0;
}