#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <vector>
#include "Matrix/Matrix.h"
#include "Vector/Vector.h"
#include "doctest.h"

TEST_CASE("Matrix::Matrix()") {
    Matrix matrix;
    CHECK_EQ(matrix.rows, 0);
    CHECK_EQ(matrix.cols, 0);
    CHECK_EQ(matrix.matrix, std::vector<std::vector<lld>>(0, std::vector<lld>(0, 0)));

    matrix = Matrix(2, 3);
    CHECK_EQ(matrix.rows, 2);
    CHECK_EQ(matrix.cols, 3);
    CHECK_EQ(matrix.matrix, std::vector<std::vector<lld>>(2, std::vector<lld>(3, 0)));

    matrix = Matrix(std::vector<std::vector<lld>>({{1, 2, 3},
                                                   {4, 5, 6}}));
    CHECK_EQ(matrix.rows, 2);
    CHECK_EQ(matrix.cols, 3);
    CHECK_EQ(matrix.matrix, std::vector<std::vector<lld>>({{1, 2, 3},
                                                           {4, 5, 6}}));

    matrix = Matrix("[1 2 3; 4 5 6; 7 8 9]");
    CHECK_EQ(matrix.rows, 3);
    CHECK_EQ(matrix.cols, 3);
    CHECK_EQ(matrix.matrix, std::vector<std::vector<lld>>({{1, 2, 3},
                                                           {4, 5, 6},
                                                           {7, 8, 9}}));
}

TEST_CASE("Matrix::print") {
    Matrix matrix = Matrix("[1 2 3; 4 5 6; 7 8 9]");
    matrix.print();
}

TEST_CASE("Matrix::operators") {
    Matrix m1, m2, m3;
    m1 = Matrix("[1 2 3; 4 5 6; 7 8 9]");
    m2 = Matrix("[1 0 0; 0 1 0; 0 0 1]"); // Identity matrix
    m3 = m1 + m2;
    CHECK_EQ(m3.matrix, std::vector<std::vector<lld>>({{2, 2, 3},
                                                       {4, 6, 6},
                                                       {7, 8, 10}}));
    m3 = m1 - m2;
    CHECK_EQ(m3.matrix, std::vector<std::vector<lld>>({{0, 2, 3},
                                                       {4, 4, 6},
                                                       {7, 8, 8}}));
    m3 = m1 * m1;
    CHECK_EQ(m3.matrix, std::vector<std::vector<lld>>({{30,  36,  42},
                                                       {66,  81,  96},
                                                       {102, 126, 150}}));
    m3 = m1.transpose();
    CHECK_EQ(m3.matrix, std::vector<std::vector<lld>>({{1, 4, 7},
                                                       {2, 5, 8},
                                                       {3, 6, 9}}));
    m3 = m1 * 2;
    CHECK_EQ(m3.matrix, std::vector<std::vector<lld>>({{2,  4,  6},
                                                       {8,  10, 12},
                                                       {14, 16, 18}}));
    m3 = m1 / 2;
    CHECK_EQ(m3.matrix, std::vector<std::vector<lld>>({{0.5, 1,   1.5},
                                                       {2,   2.5, 3},
                                                       {3.5, 4,   4.5}}));

    m2 = Matrix("[1 2 3; 4 5 6]");
    CHECK_THROWS(m3 = m1 + m2);
    CHECK_THROWS(m3 = m1 - m2);
    CHECK_THROWS(m3 = m1 * m2);
    CHECK_THROWS(m3 = m1 / 0);
}

TEST_CASE("Matrix * Vector") {
    Matrix m1;
    Vector a1, a2;
    m1 = Matrix("[1 2 3; 4 5 6; 7 8 9]");
    a1 = Vector("[1 2 3]");
    a2 = m1 * a1;
    CHECK_EQ(a2.array, std::vector<lld>{14, 32, 50});
    a2 = a1 * m1;
    CHECK_EQ(a2.array, std::vector<lld>{30, 36, 42});
    a1 = Vector("[1 2 3 4 5 6 7 8 9 10]");
    CHECK_THROWS(a2 = m1 * a1);
    CHECK_THROWS(a2 = a1 * m1);

    a1 = Vector("[1 2 3]");
    a2 = Vector("[1 2 3]");
    m1 = product(a1, a2);
    CHECK_EQ(m1.matrix, std::vector<std::vector<lld>>({{1, 2, 3},
                                                       {2, 4, 6},
                                                       {3, 6, 9}}));
}