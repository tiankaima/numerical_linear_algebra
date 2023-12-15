//
// Created by tiankaima on 23-12-16.
//

#include "CustomMath_lib.h"
#include "../doctest.h"

TEST_CASE("HW 6.1") {
    auto a_list = std::vector<Vector>{ //
            Vector(std::vector<lld>{1, -5, 3}), //
            Vector(std::vector<lld>{0, -3, -1}), //
            Vector(std::vector<lld>{101, 208.01, 10891.01, 9802.08, 79108.9, -99902, 790, -1000}) //
    };

    for (auto &a: a_list) {
        auto max_root = MaxRootForPolynomial(a);
    }
}

TEST_CASE("HW 6/hessenberg_test(") {
    auto m = Matrix(std::vector<std::vector<lld>>{ //
            {1.0,  2.9,  3.8,  4.7}, //
            {5.6,  6.5,  7.4,  8.3}, //
            {9.2,  10.1, 11.0, 12.9}, //
            {13.8, 14.7, 15.6, 16.5} //
    });
    Matrix u;
    HessenbergMethod_Inplace(m, u);
    auto test = u.transpose() * m * u;
}

void par_2_2() {
    auto coefficients = Vector(41);
    coefficients.array[41 - 3 + 1] = 1;
    coefficients.array[41 - 1] = 1;

    auto result = AllRootsForPolynomial(coefficients);
}

void par_2_3() {
    auto m = Matrix(std::vector<std::vector<lld>>{{1.0,  2.9,  3.8,  4.7},
                                                  {5.6,  6.5,  7.4,  8.3},
                                                  {9.2,  10.1, 11.0, 12.9},
                                                  {13.8, 14.7, 15.6, 16.5}});

    auto h = QRMethod(m);
    auto k = AllEigenValues(h.result);

    m = Matrix(std::vector<std::vector<lld>>{{2, 3, 4, 5, 6},
                                             {4, 4, 5, 6, 7},
                                             {0, 3, 6, 7, 8},
                                             {0, 0, 2, 8, 9},
                                             {0, 0, 0, 1, 10}});

    h = QRMethod(m);
    k = AllEigenValues(h.result);

    auto x_list = std::vector<lld>{0.9, 1.0, 1.1};
    for (auto x: x_list) {
        m = Matrix(std::vector<std::vector<lld>>{{9.1, 3.0, 2.6, 4.0},
                                                 {4.2, 5.3, 4.7, 1.6},
                                                 {3.2, 1.7, 9.4, x},
                                                 {6.1, 4.9, 3.5, 6.2}});

        h = QRMethod(m);
        k = AllEigenValues(h.result);
    }
}

TEST_CASE("HW 6.2") {
    par_2_2();
    par_2_3();
}