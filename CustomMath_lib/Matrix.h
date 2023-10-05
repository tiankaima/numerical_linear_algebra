//
// Created by Tiankai Ma on 2023/10/5.
//

#ifndef NUMERICAL_ALGEBRA_MATRIX_H
#define NUMERICAL_ALGEBRA_MATRIX_H

#include "vector"
#include "Array.h"
#include "string"
#include "iostream"
#include "Array.h"
#include "cmath"

class Matrix {
public:
    std::vector<std::vector<long double>> matrix;
    unsigned long rows;
    unsigned long cols;

    Matrix();

    Matrix(unsigned long rows, unsigned long cols);

    Matrix(const Matrix &other);

    explicit Matrix(std::vector<std::vector<long double>> matrix);

    explicit Matrix(std::string matlab_matrix);

    static Matrix identity(unsigned long n); // Identity matrix

    void print();

    Matrix operator+(const Matrix &other);

    Matrix operator-(const Matrix &other);

    Matrix operator*(const Matrix &other);

    Matrix transpose();

//    Matrix inverse();

    Matrix operator*(double scalar);

    Matrix operator/(double scalar);

    Array operator*(const Array &other);

    bool operator==(const Matrix &other) const;

    static Matrix product(const Array &array1, const Array &array2);

    [[nodiscard]] bool isSquare() const;

    void requireSquare() const;
};


#endif //NUMERICAL_ALGEBRA_MATRIX_H