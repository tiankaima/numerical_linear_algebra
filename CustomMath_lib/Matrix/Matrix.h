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

#define CHECK_SQUARE_MATRIX(matrix) \
    if (!matrix->isSquare()) { \
        throw std::invalid_argument("The matrix is not a square matrix."); \
    }

#define CHECK_SQUARE_MATRIX_REF(matrix) \
    if (!matrix.isSquare()) { \
        throw std::invalid_argument("The matrix is not a square matrix."); \
    }

#define CHECK_EQUAL_SIZE(matrix, vector) \
    if (matrix->rows != vector->size) { \
        throw std::invalid_argument("Matrix and vector dimensions must agree."); \
    }

#define CHECK_EQUAL_SIZE_REF(matrix, vector) \
    if (matrix.rows != vector.size) { \
        throw std::invalid_argument("Matrix and vector dimensions must agree."); \
    }

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

    Matrix operator*(double scalar);

    Matrix operator/(double scalar);

    Vector operator*(const Vector &other);

    bool operator==(const Matrix &other) const;

    static Matrix product(const Vector &array1, const Vector &array2);

    [[nodiscard]] bool isSquare() const;
};


#endif //NUMERICAL_ALGEBRA_MATRIX_H