//
// Created by Tiankai Ma on 2023/10/5.
//

#ifndef NUMERICAL_ALGEBRA_VECTOR_H
#define NUMERICAL_ALGEBRA_VECTOR_H

#include "vector"
#include "string"
#include "iostream"
#include "cmath"

class Matrix;

class Vector {
public:
    std::vector<long double> array;
    unsigned long size;

    Vector();

    Vector(const Vector &other);

    explicit Vector(unsigned int size);

    explicit Vector(const std::vector<long double> &array);

    explicit Vector(std::string matlab_array);

    void print();

    Vector operator+(const Vector &other);

    Vector operator-(const Vector &other);

    long double operator*(const Vector &other);

    Vector operator*(long double scalar);

    Vector operator/(long double scalar);

    Vector operator*(const Matrix &other);

    bool operator==(const Vector &other) const;

    [[nodiscard]] long double norm() const;
};

#endif //NUMERICAL_ALGEBRA_VECTOR_H
