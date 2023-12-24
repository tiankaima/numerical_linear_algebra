//
// Created by TianKai Ma on 2023/12/15.
//

#include "Matrix.h"

Matrix Matrix::sub_matrix(ull start_row, ull end_row, ull start_col, ull end_col) const {
#ifdef DEBUG
    if (end_row < start_row || end_col < start_col) {
        throw std::invalid_argument("Invalid sub_matrix size.");
    }

    if (end_row > this->rows || end_col > this->cols) {
        throw std::invalid_argument("Invalid index.");
    }
#endif

    auto result = Matrix(end_row - start_row, end_col - start_col);
    for (ull i = start_row; i < end_row; i++) {
        for (ull j = start_col; j < end_col; j++) {
            result.matrix[i - start_row][j - start_col] = this->matrix[i][j];
        }
    }
    return result;
}

[[nodiscard]] Vector Matrix::sub_array_r(ull row, ull start_col, ull end_col) const {
#ifdef DEBUG
    if (end_col < start_col) {
        throw std::invalid_argument("Invalid sub_array size.");
    }

    if (row > this->rows || end_col > this->cols) {
        throw std::invalid_argument("Invalid index.");
    }
#endif

    auto result = Vector(end_col - start_col);
    for (ull i = start_col; i < end_col; i++) {
        result.array[i - start_col] = this->matrix[row][i];
    }
    return result;
}

[[nodiscard]] Vector Matrix::sub_array_c(ull start_row, ull end_row, ull col) const {
#ifdef DEBUG
    if (end_row < start_row) {
        throw std::invalid_argument("Invalid sub_array size.");
    }

    if (end_row > this->rows || col > this->cols) {
        throw std::invalid_argument("Invalid index.");
    }
#endif

    auto result = Vector(end_row - start_row);
    for (ull i = start_row; i < end_row; i++) {
        result.array[i - start_row] = this->matrix[i][col];
    }
    return result;
}

Matrix Matrix::sub_diagonal() const {
#ifdef DEBUG
    if (!this->isSquare()) {
        throw std::invalid_argument("Matrix must be square.");
    }
#endif

    auto result = Matrix(this->rows, this->cols);
    for (ull i = 0; i < this->rows; i++) {
        result.matrix[i][i] = this->matrix[i][i];
    }
    return result;
}

Matrix Matrix::sub_upperTriangle() const {
#ifdef DEBUG
    if (!this->isSquare()) {
        throw std::invalid_argument("Matrix must be square.");
    }
#endif

    auto result = Matrix(this->rows, this->cols);
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = i + 1; j < this->cols; j++) {
            result.matrix[i][j] = this->matrix[i][j];
        }
    }
    return result;
}

Matrix Matrix::sub_lowerTriangle() const {
#ifdef DEBUG
    if (!this->isSquare()) {
        throw std::invalid_argument("Matrix must be square.");
    }
#endif

    auto result = Matrix(this->rows, this->cols);
    for (ull i = 1; i < this->rows; i++) {
        for (ull j = 0; j < i; j++) {
            result.matrix[i][j] = this->matrix[i][j];
        }
    }
    return result;
}

void Matrix::set(ull start_row, ull end_row, ull start_col, ull end_col, const Matrix &other) {
#ifdef DEBUG
    if (end_row < start_row || end_col < start_col) {
        throw std::invalid_argument("Invalid sub_matrix size.");
    }

    if (end_row > this->rows || end_col > this->cols) {
        throw std::invalid_argument("Invalid index.");
    }

    if (end_row - start_row != other.rows || end_col - start_col != other.cols) {
        throw std::invalid_argument("Invalid sub_matrix size.");
    }
#endif

    for (ull i = start_row; i < end_row; i++) {
        for (ull j = start_col; j < end_col; j++) {
            this->matrix[i][j] = other.matrix[i - start_row][j - start_col];
        }
    }
}

void Matrix::set_r(ull row, ull start_col, ull end_col, const Vector &other) {
#ifdef DEBUG
    if (end_col < start_col) {
        throw std::invalid_argument("Invalid sub_array size.");
    }

    if (row > this->rows || end_col > this->cols) {
        throw std::invalid_argument("Invalid index.");
    }

    if (end_col - start_col != other.size) {
        throw std::invalid_argument("Invalid sub_array size.");
    }
#endif

    for (ull i = start_col; i < end_col; i++) {
        this->matrix[row][i] = other.array[i - start_col];
    }
}

void Matrix::set_c(ull start_row, ull end_row, ull col, const Vector &other) {
#ifdef DEBUG
    if (end_row < start_row) {
        throw std::invalid_argument("Invalid sub_array size.");
    }

    if (end_row > this->rows || col > this->cols) {
        throw std::invalid_argument("Invalid index.");
    }

    if (end_row - start_row != other.size) {
        throw std::invalid_argument("Invalid sub_array size.");
    }
#endif

    for (ull i = start_row; i < end_row; i++) {
        this->matrix[i][col] = other.array[i - start_row];
    }
}