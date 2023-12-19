#include "CustomMath_lib.h"

int main() {
    for (auto type: {JACOBI_METHOD_TYPE_CLASSIC, JACOBI_METHOD_TYPE_LOOP, JACOBI_METHOD_TYPE_THRESHOLD}) {
        auto m = Matrix("[5 1 -2; 1 2 0; -2 0 -10]");
        auto r = JacobiMethod(m, type);

        r.result.A.print();
        r.result.P.print();

        (r.result.P.transpose() * r.result.A * r.result.P).print();

        std::cout << r.iteration_count << std::endl;
        std::cout << r.time_cost.count() << std::endl;
    }

    return 0;
}