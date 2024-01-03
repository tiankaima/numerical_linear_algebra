#include "includes/NLAMethods.h"

// homework 8 (SVD):
int main() {
    auto A = Matrix(10, 8, 1, 10);
    auto r = SVDMethod(A);

    A.print();

    r.B.print();

    (r.U * A * r.V).clean(1e-5).print();

    (r.U.transpose() * r.U).print();
    (r.V.transpose() * r.V).print();

    return 0;

//    auto A = Matrix("[1 2; 0 4]");
//
//    auto r = WilkinsonShiftIteration2D(A);
//
//    r.B.print();
//    (r.P.transpose() * A * r.Q.transpose()).print();
//
//    return 0;
}