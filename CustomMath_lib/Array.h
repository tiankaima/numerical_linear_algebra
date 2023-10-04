//
// Created by Tiankai Ma on 2023/10/5.
//

#ifndef NUMERICAL_ALGEBRA_ARRAY_H
#define NUMERICAL_ALGEBRA_ARRAY_H

#include <vector>

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

    Array operator+(Array &other);

    Array operator-(Array &other);

    double operator*(Array &other);

    Array operator*(double scalar);

    Array operator/(double scalar);

    Array operator*(Matrix &other);
};

#endif //NUMERICAL_ALGEBRA_ARRAY_H
