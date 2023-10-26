//
// Created by Tiankai Ma on 2023/10/5.
//

#ifndef NUMERICAL_ALGEBRA_MATRIX_H
#define NUMERICAL_ALGEBRA_MATRIX_H

#include "vector"
#include "random"
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

    Matrix(ull rows, ull cols, lld default_value);

    /*
     * Generate a matrix with random values in range [lower_bound, upper_bound]
     */
    Matrix(ull rows, ull cols, lld lower_bound, lld upper_bound);

    Matrix(const Matrix &other);

    explicit Matrix(std::vector<std::vector<lld>> matrix);

    explicit Matrix(std::string matlab_matrix);

    static Matrix identity(ull n); // Identity matrix

    void print();

    Matrix operator+(const Matrix &other) const;

    Matrix operator-(const Matrix &other) const;

    Matrix operator*(const Matrix &other) const;

    Matrix transpose() const;

    Matrix operator*(double scalar) const;

    Matrix operator/(double scalar) const;

    Vector operator*(const Vector &other) const;

    bool operator==(const Matrix &other) const;

    bool isSquare() const;

    static Matrix hilbert(ull n);

    static Matrix UpperTriangular(ull n, lld default_value);

    static Matrix LowerTriangular(ull n, lld default_value);

    static Matrix Diagonal(ull n, lld default_value);
};

Matrix product(const Vector &array1, const Vector &array2);

#endif //NUMERICAL_ALGEBRA_MATRIX_H