//
// Created by Tiankai Ma on 2023/10/5.
//

#ifndef NUMERICAL_ALGEBRA_ARRAY_H
#define NUMERICAL_ALGEBRA_ARRAY_H

#include <vector>
#include "string"

class Matrix;

class Array {
public:
    std::vector<double> array;
    unsigned long size;

    Array();

    explicit Array(int size);

    explicit Array(std::vector<double> array);

    explicit Array(std::string matlab_array);

    void print();

    Array operator+(const Array &other);

    Array operator-(const Array &other);

    double operator*(const Array &other);

    Array operator*(double scalar);

    Array operator/(double scalar);

    Array operator*(const Matrix &other);

    bool operator==(const Array &other) const;
};

#endif //NUMERICAL_ALGEBRA_ARRAY_H
