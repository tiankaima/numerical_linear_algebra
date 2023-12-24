//
// Created by Tiankai Ma on 2023/10/5.
//

#include "../../includes/NLAMethods.h"
#include "../doctest.h"

TEST_CASE("Vector/Vector") {
    Vector vector;
    CHECK_EQ(vector.size, 0);
    CHECK_EQ(vector.array, std::vector<lld>{});

    vector = Vector(2);
    CHECK_EQ(vector.size, 2);
    CHECK_EQ(vector.array, std::vector<lld>{0, 0});

    vector = Vector(2, 3);
    CHECK_EQ(vector.size, 2);
    CHECK_EQ(vector.array, std::vector<lld>{3, 3});

    vector = Vector(2, 3, 5);
    CHECK_EQ(vector.size, 2);
    for (int i = 0; i < vector.size; i++) {
        CHECK_GE(vector.array[i], 3);
        CHECK_LE(vector.array[i], 5);
    }

    vector = Vector(std::vector<lld>{1, 2, 3});
    CHECK_EQ(vector.size, 3);
    CHECK_EQ(vector.array, std::vector<lld>{1, 2, 3});

    vector = Vector("[1 2 3]");
    CHECK_EQ(vector.size, 3);
    CHECK_EQ(vector.array, std::vector<lld>{1, 2, 3});

    vector.print();

    vector = Vector("[1 2 3]");
    Vector vector_sub;
    CHECK_THROWS(vector_sub = vector.sub_vector(0, 4));
    CHECK_THROWS(vector_sub = vector.sub_vector(2, 0));
    vector_sub = vector.sub_vector(1, 3);
    CHECK_EQ(vector_sub, Vector("[2 3]"));

    CHECK_THROWS(vector.set(0, 4, Vector("[1 2 3]")));
    CHECK_THROWS(vector.set(0, 2, Vector("[1 2 3]")));
    CHECK_THROWS(vector.set(2, 0, Vector("[1 2 3]")));
    vector.set(1, 3, Vector("[4 5]"));
    CHECK_EQ(vector, Vector("[1 4 5]"));

    auto array1 = Vector("[1 2 3]");
    auto array2 = Vector("[4 5 6]");

    auto array3 = array1 + array2;
    CHECK_EQ(array3, Vector("[5 7 9]"));

    array3 = array2 - array1;
    CHECK_EQ(array3, Vector("[3 3 3]"));

    array3 = array1 * 2;
    CHECK_EQ(array3, Vector("[2 4 6]"));

    array3 = 2 * array1;
    CHECK_EQ(array3, Vector("[2 4 6]"));

    array3 = array1 / 2;
    CHECK_EQ(array3, Vector("[0.5 1 1.5]"));

    lld dot_product = array1 * array2;
    CHECK_EQ(dot_product, 32);

    array3 = Vector("[1 2 3 4 5 6 7 8 9 10]");
    CHECK_THROWS(array3 = array1 + array3);
    CHECK_THROWS(array3 = array1 - array3);
    CHECK_THROWS(dot_product = array1 * array3);

    CHECK_EQ(array1 == array2, false);
    CHECK_EQ(array1 == array3, false);
    CHECK_EQ(cmp(array1.norm(), std::sqrt(14)), true);

    array1 = Vector("[0 1 -2 0]");
    CHECK_EQ(sign(array1), Vector("[0 1 -1 0]"));
}