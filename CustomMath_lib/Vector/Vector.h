//
// Created by Tiankai Ma on 2023/10/5.
//

#ifndef NUMERICAL_ALGEBRA_VECTOR_H
#define NUMERICAL_ALGEBRA_VECTOR_H

#include "base.h"

class Matrix;

class Vector {
public:
    std::vector<lld> array;
    ull size;

    Vector();

    Vector(const Vector &other);

    explicit Vector(ull size);

    Vector(ull size, lld default_value);

    Vector(ull size, double lower_bound, double upper_bound);

    explicit Vector(const std::vector<lld> &array);

    explicit Vector(std::string matlab_array);

    [[nodiscard]] Vector sub_vector(ull start, ull end) const;

    void set(ull start, ull end, const Vector &other);

    void print();

    Vector operator+(const Vector &other) const;

    Vector operator-(const Vector &other) const;

    lld operator*(const Vector &other) const;

    Vector operator*(lld scalar) const;

    Vector operator/(lld scalar) const;

    Vector operator*(const Matrix &other) const;

    bool operator==(const Vector &other) const;

    [[nodiscard]] lld norm() const;
};

Vector sign(const Vector &vector);

#endif //NUMERICAL_ALGEBRA_VECTOR_H
