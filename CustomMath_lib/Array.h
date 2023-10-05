//
// Created by Tiankai Ma on 2023/10/5.
//

#ifndef NUMERICAL_ALGEBRA_ARRAY_H
#define NUMERICAL_ALGEBRA_ARRAY_H

#include "vector"
#include "string"
#include "iostream"
#include "cmath"

class Matrix;

class Array {
public:
    std::vector<long double> array;
    unsigned long size;

    Array();

    Array(const Array &other);

    explicit Array(unsigned int size);

    explicit Array(const std::vector<long double> &array);

    explicit Array(std::string matlab_array);

    void print();

    Array operator+(const Array &other);

    Array operator-(const Array &other);

    long double operator*(const Array &other);

    Array operator*(long double scalar);

    Array operator/(long double scalar);

    Array operator*(const Matrix &other);

    bool operator==(const Array &other) const;

    [[nodiscard]] long double norm() const;
};

#endif //NUMERICAL_ALGEBRA_ARRAY_H
