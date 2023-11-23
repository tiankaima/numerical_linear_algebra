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
    Matrix(ull rows, ull cols, double lower_bound, double upper_bound);

    // Copy constructor
    Matrix(const Matrix &other);

    explicit Matrix(std::vector<std::vector<lld>> matrix);

    /*
     * Construct a matrix from a string in MATLAB format.
     */
    explicit Matrix(std::string matlab_matrix);

    /*
     * extract a sub-matrix from the matrix
     */
    [[nodiscard]] Matrix sub_matrix(ull start_row, ull end_row, ull start_col, ull end_col) const;

    [[nodiscard]] Matrix sub_diagonal() const;

    [[nodiscard]] Matrix sub_upperTriangle() const;

    [[nodiscard]] Matrix sub_lowerTriangle() const;

    void set(ull start_row, ull end_row, ull start_col, ull end_col, const Matrix &other);

    void print();

    Matrix operator+(const Matrix &other) const;

    Matrix operator-(const Matrix &other) const;

    Matrix operator*(const Matrix &other) const;

    [[nodiscard]] Matrix transpose() const;

    /*
     * Return the inverse of the matrix(supposing it is a diagonal matrix)
     */
    [[nodiscard]] Matrix diagonal_inverse() const;

    Matrix operator*(lld scalar) const;

    Matrix operator/(lld scalar) const;

    Vector operator*(const Vector &other) const;

    bool operator==(const Matrix &other) const;

    [[nodiscard]] bool isSquare() const;

    static Matrix identity(ull n); // Identity matrix

    static Matrix hilbert(ull n);

    static Matrix UpperTriangular(ull n, lld default_value);

    static Matrix LowerTriangular(ull n, lld default_value);

    static Matrix Diagonal(ull n, lld default_value);
};

Matrix product(const Vector &array1, const Vector &array2);

#endif //NUMERICAL_ALGEBRA_MATRIX_H