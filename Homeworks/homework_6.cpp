//
// Created by TianKai Ma on 2023/12/14.
//

#include "homework_6.h"

void par_1_each(Vector &a) {
    auto max_root = MaxRootForPolynomial(a);

    std::cout << "Polynomial is ";
    a.print();
    std::cout << "Max root for polynomial is " << std::setprecision(10) << max_root.x << std::endl;
    std::cout << "Iteration times is " << max_root.iteration_times << std::endl;
    std::cout << "Time cost is " << max_root.time_cost.count() << " microseconds" << std::endl;
}


void par_1() {
    std::cout << "------ Q 6.1 ------" << std::endl;

    auto a_list = std::vector<Vector>{ //
            Vector(std::vector<lld>{1, -5, 3}), //
            Vector(std::vector<lld>{0, -3, -1}), //
            Vector(std::vector<lld>{101, 208.01, 10891.01, 9802.08, 79108.9, -99902, 790, -1000}) //
    };

    for (auto &a: a_list) {
        par_1_each(a);
    }
}

void hessenberg_test() {
    auto m = Matrix(std::vector<std::vector<lld>>{ //
            {1.0,  2.9,  3.8,  4.7}, //
            {5.6,  6.5,  7.4,  8.3}, //
            {9.2,  10.1, 11.0, 12.9}, //
            {13.8, 14.7, 15.6, 16.5} //
    });
    m.print();
    Matrix u;
    HessenbergMethod_Inplace(m, u);
    m.print();
    u.print();
    auto test = u.transpose() * m * u;
    test.print();
}

void par_2_2() {
    std::cout << std::endl << "------ Q 6.2(2) ------" << std::endl;

//    auto coefficients = Vector(std::vector<lld>{1, -5, 3});
    auto coefficients = Vector(41);
    coefficients.array[41 - 3 + 1] = 1;
    coefficients.array[41 - 1] = 1;

    auto result = AllRootsForPolynomial(coefficients);
    std::cout << "Roots for polynomial are:" << std::endl;
    result.result.print();
    std::cout << "Iteration times is " << result.iteration_times << std::endl;
    std::cout << "Time cost is " << result.time_cost.count() << " microseconds" << std::endl;
}

void par_2_3() {
    std::cout << std::endl << "------ Q 6.2(3) ------" << std::endl;

//    auto m = Matrix(std::vector<std::vector<lld>>{
//            {1.0,  2.9,  3.8,  4.7},
//            {5.6,  6.5,  7.4,  8.3},
//            {9.2,  10.1, 11.0, 12.9},
//            {13.8, 14.7, 15.6, 16.5}
//    });
//    auto m = Matrix(std::vector<std::vector<lld>>{
//            {2,3,4,5,6},
//            {4,4,5,6,7},
//            {0,3,6,7,8},
//            {0,0,2,8,9},
//            {0,0,0,1,10}
//    });
    auto x_list = std::vector<lld>{0.9, 1.0, 1.1};
    for (auto x: x_list) {
        std::cout << "x = " << x << std::endl;
        auto m = Matrix(std::vector<std::vector<lld>>{{9.1, 3.0, 2.6, 4.0},
                                                      {4.2, 5.3, 4.7, 1.6},
                                                      {3.2, 1.7, 9.4, x},
                                                      {6.1, 4.9, 3.5, 6.2}});

        auto h = QRMethod(m);
        auto k = AllEigenValues(h.result);
        std::cout << "Eigen values are:" << std::endl;
        print_llc(k);
        std::cout << "Iteration times is " << h.iteration_times << std::endl;
        std::cout << "Time cost is " << h.time_cost.count() << " microseconds" << std::endl;

        std::cout << std::endl;
    }
}

void par_2() {
    par_2_2();
    par_2_3();
}

int homework_6() {
//    hessenberg_test();

    par_1();
    par_2();
    return 0;
}