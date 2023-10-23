//
// Created by Tiankai Ma on 2023/10/5.
//

#include <vector>
#include <string>
#include "Matrix/Matrix.h"
#include "Vector/Vector.h"
#include "doctest.h"

TEST_CASE("Vector::Vector()") {
    Vector array;
    CHECK(array.size == 0);

    array = Vector(2);
    CHECK(array.size == 2);

    array = Vector(std::vector<long double>{1, 2, 3});
    CHECK(array.size == 3);
    CHECK(array.array == std::vector<long double>{1, 2, 3});

    array = Vector("[1 2 3]");
    CHECK(array.size == 3);
    CHECK(array.array == std::vector<long double>{1, 2, 3});
}

TEST_CASE("Vector::print()") {
    Vector array = Vector("[1 2 3]");
    array.print();
}

TEST_CASE("Vector::operator+()") {
    Vector array1, array2, array3;
    array1 = Vector("[1 2 3]");
    array2 = Vector("[4 5 6]");
    array3 = array1 + array2;
    CHECK(array3.array == std::vector<long double>{5, 7, 9});
    array3 = array2 - array1;
    CHECK(array3.array == std::vector<long double>{3, 3, 3});
    array3 = array1 * 2;
    CHECK(array3.array == std::vector<long double>{2, 4, 6});
    array3 = array1 / 2;
    CHECK(array3.array == std::vector<long double>{0.5, 1, 1.5});
    long double dot_product = array1 * array2;
    CHECK(dot_product == 32);

    array3 = Vector("[1 2 3 4 5 6 7 8 9 10]");
    CHECK_THROWS(array3 = array1 + array3);
    CHECK_THROWS(array3 = array1 - array3);
    CHECK_THROWS(dot_product = array1 * array3);
}