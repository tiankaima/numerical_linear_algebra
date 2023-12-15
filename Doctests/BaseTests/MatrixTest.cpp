#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "CustomMath_lib.h"
#include "../doctest.h"

TEST_CASE("Matrix/MatrixGenerations)") {
    Matrix matrix;
    CHECK_EQ(matrix.rows, 0);
    CHECK_EQ(matrix.cols, 0);
    CHECK_EQ(matrix.matrix, std::vector<std::vector<lld>>(0, std::vector<lld>(0, 0)));

    matrix = Matrix(2, 3);
    CHECK_EQ(matrix.rows, 2);
    CHECK_EQ(matrix.cols, 3);
    CHECK_EQ(matrix.matrix, std::vector<std::vector<lld>>(2, std::vector<lld>(3, 0)));

    matrix = Matrix(2, 3, 2);
    CHECK_EQ(matrix.rows, 2);
    CHECK_EQ(matrix.cols, 3);
    CHECK_EQ(matrix.matrix, std::vector<std::vector<lld>>(2, std::vector<lld>(3, 2)));

    matrix = Matrix(2, 3, 1, 10);
    CHECK_EQ(matrix.rows, 2);
    CHECK_EQ(matrix.cols, 3);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            CHECK_GE(matrix.matrix[i][j], 1);
            CHECK_LE(matrix.matrix[i][j], 10);
        }
    }

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

    matrix = Matrix::identity(4);
    CHECK_EQ(matrix.rows, 4);
    CHECK_EQ(matrix.cols, 4);
    CHECK_EQ(matrix.matrix, std::vector<std::vector<lld>>({{1, 0, 0, 0},
                                                           {0, 1, 0, 0},
                                                           {0, 0, 1, 0},
                                                           {0, 0, 0, 1}}));

    matrix = Matrix::hilbert(3);
    CHECK_EQ(matrix.rows, 3);
    CHECK_EQ(matrix.cols, 3);
    auto target_matrix = Matrix(std::vector<std::vector<lld>>({{1.0,     1.0 / 2, 1.0 / 3},
                                                               {1.0 / 2, 1.0 / 3, 1.0 / 4},
                                                               {1.0 / 3, 1.0 / 4, 1.0 / 5}}));
    CHECK_EQ(matrix, target_matrix);

    matrix = Matrix::UpperTriangular(3, 1);
    CHECK_EQ(matrix.rows, 3);
    CHECK_EQ(matrix.cols, 3);
    CHECK_EQ(matrix.matrix, std::vector<std::vector<lld>>({{1, 1, 1},
                                                           {0, 1, 1},
                                                           {0, 0, 1}}));

    matrix = Matrix::LowerTriangular(3, 1);
    CHECK_EQ(matrix.rows, 3);
    CHECK_EQ(matrix.cols, 3);
    CHECK_EQ(matrix.matrix, std::vector<std::vector<lld>>({{1, 0, 0},
                                                           {1, 1, 0},
                                                           {1, 1, 1}}));

    matrix = Matrix::Diagonal(3, 1);
    CHECK_EQ(matrix.rows, 3);
    CHECK_EQ(matrix.cols, 3);
    CHECK_EQ(matrix.matrix, std::vector<std::vector<lld>>({{1, 0, 0},
                                                           {0, 1, 0},
                                                           {0, 0, 1}}));
}

TEST_CASE("Matrix/MatrixOperations") {
    auto m1 = Matrix("[1 2 3; 4 5 6; 7 8 9]");
    auto m2 = Matrix("[1 0 0; 0 1 0; 0 0 1]");
    auto m3 = m1 + m2;
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
    m3 = 2 * m1;
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

    auto a1 = Vector("[1 2 3]");

    auto a2 = m1 * a1;
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

TEST_CASE("Matrix/MatrixProperties") {
    auto m = Matrix("[1 2 3; 4 5 6; 7 8 9]");
    m.matrix[2][2] = 1e-11;
    m = m.clean();
    CHECK_EQ(m.matrix, std::vector<std::vector<lld>>({{1, 2, 3},
                                                      {4, 5, 6},
                                                      {7, 8, 0}}));


    m = Matrix("[1 2 3; 4 5 6; 7 8 9]");
    m.print();
    m = m.transpose();
    CHECK_EQ(m.matrix, std::vector<std::vector<lld>>({{1, 4, 7},
                                                      {2, 5, 8},
                                                      {3, 6, 9}}));

    m = Matrix("[1 0 0; 0 2 0; 0 0 4]");
    m = m.diagonal_inverse();
    auto target_matrix = Matrix("[1 0 0; 0 0.5 0; 0 0 0.25]");
    CHECK_EQ(m, target_matrix);

    auto m2 = Matrix("[1 2 3; 4 5 6]");
    auto m3 = Matrix("[1 2 3; 4 5 6; 7 8 10]");
    bool c;
    CHECK_EQ(m == m2, false);
    CHECK_EQ(m == m3, false);
    CHECK_THROWS(m = m2.diagonal_inverse());

    m = Matrix("[1 0 0; 4 0 0; 9 0 0]");
    CHECK_EQ(cmp(m.norm(),std::sqrt(98)), true);

    m = Matrix("[1 2 3; 4 5 6; 7 8 9]");
    CHECK_EQ(m.max(), 9);
    CHECK_EQ(m.min(), 1);
}

TEST_CASE("Matrix/MatrixSubOperations") {
    auto m = Matrix("[1 2 3; 4 5 6; 7 8 9]");
    auto m2 = m.sub_matrix(0, 1, 1, 2);
    CHECK_EQ(m2.matrix, std::vector<std::vector<lld>>({{2}}));

    CHECK_THROWS(m2 = m.sub_matrix(0, 1, 1, 4));
    CHECK_THROWS(m2 = m.sub_matrix(2, 1, 1, 2));

    m2 = m.sub_diagonal();
    CHECK_EQ(m2.matrix, std::vector<std::vector<lld>>({{1, 0, 0},
                                                       {0, 5, 0},
                                                       {0, 0, 9}}));

    m2 = m.sub_upperTriangle();
    CHECK_EQ(m2.matrix, std::vector<std::vector<lld>>({{0, 2, 3},
                                                       {0, 0, 6},
                                                       {0, 0, 0}}));

    m2 = m.sub_lowerTriangle();
    CHECK_EQ(m2.matrix, std::vector<std::vector<lld>>({{0, 0, 0},
                                                       {4, 0, 0},
                                                       {7, 8, 0}}));

    m = Matrix("[1 2 3; 4 5 6]");
    CHECK_THROWS(m2 = m.sub_diagonal());
    CHECK_THROWS(m2 = m.sub_upperTriangle());
    CHECK_THROWS(m2 = m.sub_lowerTriangle());

    m2 = Matrix("[1 2 3; 4 5 6; 7 8 9]");
    m2.set(0, 2, 1, 3, Matrix("[1 2; 3 4]"));
    CHECK_EQ(m2.matrix, std::vector<std::vector<lld>>({{1, 1, 2},
                                                       {4, 3, 4},
                                                       {7, 8, 9}}));

    m2 = Matrix("[1 2 3; 4 5 6; 7 8 9]");
    CHECK_THROWS(m2.set(0, 2, 1, 3, Matrix("[1 2 3; 4 5 6]")));
    CHECK_THROWS(m2.set(0, 2, 1, 4, Matrix("[1 2; 3 4; 5 6]")));
    CHECK_THROWS(m2.set(2, 0, 1, 4, Matrix("[1 2; 3 4; 5 6]")));
}