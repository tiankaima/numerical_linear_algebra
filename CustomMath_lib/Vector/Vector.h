//
// Created by Tiankai Ma on 2023/10/5.
//

#ifndef NUMERICAL_ALGEBRA_VECTOR_H
#define NUMERICAL_ALGEBRA_VECTOR_H

#include "vector"
#include "string"
#include "iostream"
#include "cmath"

#define ull unsigned long long
#define lld long double

class Matrix;

class Vector {
public:
    std::vector<lld> array;
    ull size;

    Vector();

    Vector(const Vector &other);

    explicit Vector(unsigned int size);

    explicit Vector(const std::vector<lld> &array);

    explicit Vector(std::string matlab_array);

    void print();

    Vector operator+(const Vector &other);

    Vector operator-(const Vector &other);

    lld operator*(const Vector &other);

    Vector operator*(lld scalar);

    Vector operator/(lld scalar);

    Vector operator*(const Matrix &other);

    bool operator==(const Vector &other) const;

    [[nodiscard]] lld norm() const;
};

#endif //NUMERICAL_ALGEBRA_VECTOR_H
