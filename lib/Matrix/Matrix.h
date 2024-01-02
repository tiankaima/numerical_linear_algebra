//
// Created by Tiankai Ma on 2023/10/5.
//

#ifndef NUMERICAL_ALGEBRA_MATRIX_H
#define NUMERICAL_ALGEBRA_MATRIX_H

#include "base.h"
#include "Vector/Vector.h"

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

    /*
     * MatrixGeneration:
     */

    /// 0 x 0
    Matrix();

    /// Copy constructor
    Matrix(const Matrix &other);

    /// rows x cols, 0
    explicit Matrix(ull rows, ull cols);

    /// rows x cols, default_value
    explicit Matrix(ull rows, ull cols, lld default_value);

    /// rows x cols, [lower_bound, upper_bound]
    explicit Matrix(ull rows, ull cols, double lower_bound, double upper_bound);

    /// 2d vector
    explicit Matrix(std::vector<std::vector<lld>> matrix);

    /// \warning this constructor is not robust / time-efficient
    /// \param matlab_matrix matlab matrix string, e.g. "[1 2 3; 4 5 6; 7 8 9]"
    explicit Matrix(std::string matlab_matrix);

    /// I_n
    [[nodiscard]] static Matrix identity(ull n);

    /// H_n
    [[nodiscard]] static Matrix hilbert(ull n);

    /// a_{ij} = default_value i <= j
    [[nodiscard]] static Matrix UpperTriangular(ull n, lld default_value);

    /// a_{ij} = default_value i >= j
    [[nodiscard]] static Matrix LowerTriangular(ull n, lld default_value);

    /// a_{ii} = default_value
    [[nodiscard]] static Matrix Diagonal(ull n, lld default_value);

    /*
     * MatrixSubOperations:
     */

    /// Return a sub-matrix of the matrix [start, end) x [start, end), both use index that start from 0
    [[nodiscard]] Matrix sub_matrix(ull start_row, ull end_row, ull start_col, ull end_col) const;

    [[nodiscard]] Vector sub_array_row(ull row, ull start_col, ull end_col) const;

    [[nodiscard]] Vector sub_array_col(ull start_row, ull end_row, ull col) const;

    /// Return only the diagonal elements of the matrix
    [[nodiscard]] Matrix sub_diagonal() const;

    /// Return only the upper triangular elements of the matrix (not including the diagonal elements)
    [[nodiscard]] Matrix sub_upperTriangle() const;

    /// Return only the lower triangular elements of the matrix (not including the diagonal elements)
    [[nodiscard]] Matrix sub_lowerTriangle() const;

    /// Set the sub-matrix of the matrix [start, end) x [start, end), both use index that start from 0
    /// \warning this is often used in conjunction with sub_matrix()
    void set(ull start_row, ull end_row, ull start_col, ull end_col, const Matrix &other);

    void set_row(ull row, ull start_col, ull end_col, const Vector &other);

    void set_col(ull start_row, ull end_row, ull col, const Vector &other);

    /*
     * MatrixProperties:
     */

    /// Print the matrix
    void print();

    /// Return a clean matrix, i.e. all elements with absolute value less than 1e-10 are set to 0
    [[nodiscard]] Matrix clean(lld eps = 1e-10) const;

    /// A -> A^T
    [[nodiscard]] Matrix transpose() const;

    /// (a_{ii}) -> (1 / a_{ii})
    [[nodiscard]] Matrix diagonal_inverse() const;

    /// A == B
    [[nodiscard]] bool operator==(const Matrix &other) const;

    /// A.rows == A.cols
    [[nodiscard]] bool isSquare() const;

    /// 2-norm
    [[nodiscard]] lld norm() const;

    /// min{a_{ij}}
    [[nodiscard]] lld min() const;

    /// max{a_{ij}}
    [[nodiscard]] lld max() const;

    /*
    * MatrixOperations:
    */

    /// Add
    /// \warning in DEBUG mode, function would check if two matrices have the same size.
    /// \warning in RELEASE mode, it would just use this.rows and this.cols
    [[nodiscard]] Matrix operator+(const Matrix &other) const;

    /// Subtract
    /// \warning in DEBUG mode, function would check if two matrices have the same size.
    /// \warning in RELEASE mode, it would just use this.rows and this.cols
    [[nodiscard]] Matrix operator-(const Matrix &other) const;

    /// Multiply
    /// \warning in DEBUG mode, function would check if two matrices can be multiplied.
    /// \warning in RELEASE mode, it would just use this.rows and other.cols
    [[nodiscard]] Matrix operator*(const Matrix &other) const;

    /// A * lambda
    [[nodiscard]] Matrix operator*(lld scalar) const;

    /// A / lambda
    [[nodiscard]] Matrix operator/(lld scalar) const;

    /// A * x
    [[nodiscard]] Vector operator*(const Vector &other) const;
};

/*
 * MatrixOperations:
 */

/// v * w^T
Matrix product(const Vector &array1, const Vector &array2);

/// lambda * A
Matrix operator*(lld scalar, const Matrix &matrix);

/// v * A
Vector operator*(const Vector &vector, const Matrix &matrix);

#endif //NUMERICAL_ALGEBRA_MATRIX_H