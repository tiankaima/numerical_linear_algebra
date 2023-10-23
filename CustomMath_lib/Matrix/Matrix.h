//
// Created by Tiankai Ma on 2023/10/5.
//

#ifndef NUMERICAL_ALGEBRA_MATRIX_H
#define NUMERICAL_ALGEBRA_MATRIX_H

#include "vector"
#include "Vector/Vector.h"
#include "string"
#include "iostream"
#include "Vector/Vector.h"
#include "cmath"

#ifdef DEBUG
#define CHECK_SQUARE_MATRIX(matrix) \
    if (!matrix.isSquare()) { \
        throw std::invalid_argument("The matrix is not a square matrix."); \
    }

#define CHECK_EQUAL_SIZE(matrix, vector) \
    if (matrix.rows != vector.size) { \
        throw std::invalid_argument("Matrix and vector dimensions must agree."); \
    }
#else
#define CHECK_SQUARE_MATRIX(matrix)
#define CHECK_EQUAL_SIZE(matrix, vector)
#endif

class Matrix {
public:
    std::vector<std::vector<long double>> matrix;
    ull rows;
    ull cols;

    Matrix();

    Matrix(ull rows, ull cols);

    Matrix(const Matrix &other);

    explicit Matrix(std::vector<std::vector<lld>> matrix);

    explicit Matrix(std::string matlab_matrix);

    static Matrix identity(ull n); // Identity matrix

    void print();

    Matrix operator+(const Matrix &other);

    Matrix operator-(const Matrix &other);

    Matrix operator*(const Matrix &other);

    Matrix transpose();

    Matrix operator*(double scalar);

    Matrix operator/(double scalar);

    Vector operator*(const Vector &other);

    bool operator==(const Matrix &other) const;

    static Matrix product(const Vector &array1, const Vector &array2);

    [[nodiscard]] bool isSquare() const;
};


#endif //NUMERICAL_ALGEBRA_MATRIX_H