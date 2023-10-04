//
// Created by Tiankai Ma on 2023/10/5.
//

#include <vector>
#include <string>
#include "Matrix.h"
#include "Array.h"
#include "doctest.h"

TEST_CASE("Array::Array()") {
    Array array;
    CHECK(array.size == 0);

    array = Array(2);
    CHECK(array.size == 2);

    array = Array(std::vector<double>{1, 2, 3});
    CHECK(array.size == 3);
    CHECK(array.array == std::vector<double>{1, 2, 3});

    array = Array("[1 2 3]");
    CHECK(array.size == 3);
    CHECK(array.array == std::vector<double>{1, 2, 3});
}

TEST_CASE("Array::print()") {
    Array array = Array("[1 2 3]");
    array.print();
}

TEST_CASE("Array::operator+()") {
    Array array1, array2, array3;
    array1 = Array("[1 2 3]");
    array2 = Array("[4 5 6]");
    array3 = array1 + array2;
    CHECK(array3.array == std::vector<double>{5, 7, 9});
    array3 = array2 - array1;
    CHECK(array3.array == std::vector<double>{3, 3, 3});
    array3 = array1 * 2;
    CHECK(array3.array == std::vector<double>{2, 4, 6});
    array3 = array1 / 2;
    CHECK(array3.array == std::vector<double>{0.5, 1, 1.5});
    double dot_product = array1 * array2;
    CHECK(dot_product == 32);

    array3=Array("[1 2 3 4 5 6 7 8 9 10]");
    CHECK_THROWS(array3 = array1 + array3);
    CHECK_THROWS(array3 = array1 - array3);
    CHECK_THROWS(dot_product = array1 * array3);
}