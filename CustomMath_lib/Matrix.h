//
// Created by Tiankai Ma on 2023/10/5.
//

#ifndef NUMERICAL_ALGEBRA_MATRIX_H
#define NUMERICAL_ALGEBRA_MATRIX_H

#include <vector>
#include "Array.h"

class Matrix {
public:
    std::vector<std::vector<double>> matrix;
    unsigned long rows;
    unsigned long cols;

    Matrix();

    Matrix(int rows, int cols);

    explicit Matrix(std::vector<std::vector<double>> matrix);

    explicit Matrix(std::string matlab_matrix);

    void print();

    Matrix operator+(Matrix &other);

    Matrix operator-(Matrix &other);

    Matrix operator*(Matrix &other);

    Matrix transpose();

    Matrix inverse();

    Matrix operator*(double scalar);

    Matrix operator/(double scalar);

    Array operator*(Array &other);
};

Matrix product(Array &array1, Array &array2);

#endif //NUMERICAL_ALGEBRA_MATRIX_H