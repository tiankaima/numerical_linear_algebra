#include "includes/NLAMethods.h"

// homework 8 (SVD):
int main() {
    auto A = Matrix(5, 3, 1, 10);
//    A.print();

    auto r = BidiagonalizationMethod(A);

    r.B.print();
//    r.U.print();
//    r.V.print();

    (r.U * A * r.V).print();

    return 0;
}