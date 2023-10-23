//
// Created by Tiankai Ma on 2023/10/5.
//

#include "Matrix.h"

Matrix::Matrix() {
    this->rows = 0;
    this->cols = 0;
    this->matrix = std::vector<std::vector<lld>>(0, std::vector<lld>(0, 0));
}

Matrix::Matrix(ull rows, ull cols) {
    // Frankly you shouldn't use this, but why not?
    this->rows = rows;
    this->cols = cols;
    this->matrix = std::vector<std::vector<lld>>(rows, std::vector<lld>(cols, 0));
}

Matrix::Matrix(std::vector<std::vector<lld>> matrix) {
    this->rows = matrix.size();
    this->cols = matrix[0].size();
    this->matrix = matrix;
}

Matrix::Matrix(std::string matlab_matrix) {
    // Testing purpose only, can ignore speed or memory efficiency
    std::vector<std::vector<lld>> result;
    std::vector<lld> row;
    for (ull i = 0; i < matlab_matrix.size(); i++) {
        if (matlab_matrix[i] == '[' || matlab_matrix[i] == ' ') {
            continue;
        } else if (matlab_matrix[i] == ';') {
            result.push_back(row);
            row.clear();
        } else if (matlab_matrix[i] == ']') {
            result.push_back(row);
            row.clear();
            break;
        } else {
            std::string number;
            while (matlab_matrix[i] != ' ' && matlab_matrix[i] != ';' && matlab_matrix[i] != ']') {
                number += matlab_matrix[i];
                i++;
            }
            row.push_back(std::stod(number));
            i--;
        }
    }
    this->rows = result.size();
    this->cols = result[0].size();
    this->matrix = result;
}

Matrix Matrix::identity(ull n) {
    auto result = Matrix(n, n);
    for (ull i = 0; i < n; i++) {
        result.matrix[i][i] = 1;
    }
    return result;
}

void Matrix::print() {
    std::cout << "[";
    for (ull i = 0; i < this->rows; i++) {
        std::cout << "[";
        for (ull j = 0; j < this->cols; j++) {
            std::cout << this->matrix[i][j];
            if (j != this->cols - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        if (i != this->rows - 1) {
            std::cout << "," << std::endl;
        }
    }
    std::cout << "]" << std::endl;
}

Matrix Matrix::operator+(const Matrix &other) {
    if (this->rows != other.rows || this->cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
    auto result = Matrix(this->rows, this->cols);
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < this->cols; j++) {
            result.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &other) {
    if (this->rows != other.rows || this->cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
    auto result = Matrix(this->rows, this->cols);
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < this->cols; j++) {
            result.matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other) {
    if (this->cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
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

Matrix Matrix::transpose() {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "ArgumentSelectionDefects"
    auto result = Matrix(this->cols, this->rows);
#pragma clang diagnostic pop
    for (ull i = 0; i < this->cols; i++) {
        for (ull j = 0; j < this->rows; j++) {
            result.matrix[i][j] = this->matrix[j][i];
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) {
    auto result = Matrix(this->rows, this->cols);
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < this->cols; j++) {
            result.matrix[i][j] = this->matrix[i][j] * scalar;
        }
    }
    return result;
}

Matrix Matrix::operator/(double scalar) {
    if (scalar == 0) {
        throw std::invalid_argument("Cannot divide by zero.");
    }
    auto result = Matrix(this->rows, this->cols);
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < this->cols; j++) {
            result.matrix[i][j] = this->matrix[i][j] / scalar;
        }
    }
    return result;
}

Vector Matrix::operator*(const Vector &other) {
    if (this->cols != other.size) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
    auto result = Vector(this->rows);
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < other.size; j++) {
            result.array[i] += this->matrix[i][j] * other.array[j];
        }
    }
    return result;
}

Vector Vector::operator*(const Matrix &other) {
    if (this->size != other.rows) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
    auto result = Vector(other.cols);
    for (ull i = 0; i < other.cols; i++) {
        for (ull j = 0; j < this->size; j++) {
            result.array[i] += this->array[j] * other.matrix[j][i];
        }
    }
    return result;
}

bool cmp(lld a, lld b) {
    return std::fabs(a - b) < 1e-6;
}

bool Matrix::operator==(const Matrix &other) const {
    if (this->rows != other.rows || this->cols != other.cols) {
        return false;
    }
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < this->cols; j++) {
            if (!cmp(this->matrix[i][j], other.matrix[i][j])) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::isSquare() const {
    return this->rows == this->cols;
}

Matrix Matrix::product(const Vector &array1, const Vector &array2) {
    auto result = Matrix(array1.size, array2.size);
    for (ull i = 0; i < array1.size; i++) {
        for (ull j = 0; j < array2.size; j++) {
            result.matrix[i][j] = array1.array[i] * array2.array[j];
        }
    }
    return result;
}

Matrix::Matrix(const Matrix &other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = other.matrix;
}
