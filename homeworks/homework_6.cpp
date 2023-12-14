//
// Created by TianKai Ma on 2023/12/14.
//

#include "homework_6.h"


void par_1() {
//    auto a = Vector(std::vector<lld> {1,-5,3});
//    auto a = Vector(std::vector<lld> {0,-3,-1});
    auto a = Vector(std::vector<lld>{101, 208.01, 10891.01, 9802.08, 79108.9, -99902, 790, -1000});

    auto max_root = MaxRootForPolynomial(a);

    std::cout << "Max root for polynomial is " << std::setprecision(10) << max_root << std::endl;
}

void hessenberg_test() {
    auto m = Matrix(std::vector<std::vector<lld>>{
            {1.0,  2.9,  3.8,  4.7},
            {5.6,  6.5,  7.4,  8.3},
            {9.2,  10.1, 11.0, 12.9},
            {13.8, 14.7, 15.6, 16.5}
    });

    m.print();

    Matrix u;

    HessenbergMethod_Inplace(m, u);

    m.print();
    u.print();

    auto test = u.transpose() * m * u;
    test.print();
//
//    auto hessenberg = HessenbergMethod(m);
//    std::cout << "Hessenberg matrix is " << std::endl;
//    hessenberg.print();
}

void par_2() {
//    auto m = Matrix(std::vector<std::vector<lld>>{
//            {1.0,  2.9,  3.8,  4.7},
//            {5.6,  6.5,  7.4,  8.3},
//            {9.2,  10.1, 11.0, 12.9},
//            {13.8, 14.7, 15.6, 16.5}
//    });
    auto m = Matrix(std::vector<std::vector<lld>>{
            {2,3,4,5,6},
            {4,4,5,6,7},
            {0,3,6,7,8},
            {0,0,2,8,9},
            {0,0,0,1,10}
    });

    m.print();

    //    auto h = DoubleStepQRIteration(m);
    auto h = QRMethod(m);
    h.print();
}

int homework_6() {
//    par_1();
//    hessenberg_test();
    par_2();
    return 0;
}