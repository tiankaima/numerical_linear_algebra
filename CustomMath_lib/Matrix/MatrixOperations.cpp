//
// Created by TianKai Ma on 2023/12/15.
//

#include "Matrix.h"

Matrix Matrix::operator+(const Matrix &other) const {
#ifdef DEBUG
    if (this->rows != other.rows || this->cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
#endif

    auto result = Matrix(this->rows, this->cols);
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < this->cols; j++) {
            result.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const {
#ifdef DEBUG
    if (this->rows != other.rows || this->cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
#endif

    auto result = Matrix(this->rows, this->cols);
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < this->cols; j++) {
            result.matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const {
#ifdef DEBUG
    if (this->cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
#endif

    auto result = Matrix(this->rows, other.cols);
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < other.cols; j++) {
            for (ull k = 0; k < this->cols; k++) {
                result.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
            }
        }
    }
    return result;
}


Matrix Matrix::operator*(lld scalar) const {
    auto result = Matrix(this->rows, this->cols);
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < this->cols; j++) {
            result.matrix[i][j] = this->matrix[i][j] * scalar;
        }
    }
    return result;
}

Matrix Matrix::operator/(lld scalar) const {
#ifdef DEBUG
    if (scalar == 0) {
        throw std::invalid_argument("Cannot divide by zero.");
    }
#endif

    auto result = Matrix(this->rows, this->cols);
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < this->cols; j++) {
            result.matrix[i][j] = this->matrix[i][j] / scalar;
        }
    }
    return result;
}

Vector Matrix::operator*(const Vector &other) const {
#ifdef DEBUG
    if (this->cols != other.size) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
#endif

    auto result = Vector(this->rows);
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < other.size; j++) {
            result.array[i] += this->matrix[i][j] * other.array[j];
        }
    }
    return result;
}

Vector operator*(const Vector &vector, const Matrix &matrix) {
    CHECK_EQUAL_SIZE(matrix, vector)

    auto result = Vector(matrix.cols);
    for (ull i = 0; i < matrix.cols; i++) {
        for (ull j = 0; j < vector.size; j++) {
            result.array[i] += vector.array[j] * matrix.matrix[j][i];
        }
    }
    return result;
}

Vector operator*(const Matrix &matrix, const Vector &vector) {
#ifdef DEBUG
    if (matrix.cols != vector.size) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
#endif

    auto result = Vector(matrix.rows);
    for (ull i = 0; i < matrix.rows; i++) {
        for (ull j = 0; j < vector.size; j++) {
            result.array[i] += matrix.matrix[i][j] * vector.array[j];
        }
    }
    return result;
}

Matrix product(const Vector &array1, const Vector &array2) {
    auto result = Matrix(array1.size, array2.size);
    for (ull i = 0; i < array1.size; i++) {
        for (ull j = 0; j < array2.size; j++) {
            result.matrix[i][j] = array1.array[i] * array2.array[j];
        }
    }
    return result;
}
