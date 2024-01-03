#include "includes/NLAMethods.h"

// homework 8 (SVD):
int main() {
    auto A = Matrix(8, 8, 1, 10);
    auto r = BidiagonalizationMethod(A);

    r.B.print();

    (r.U * A * r.V).print();

    return 0;
}