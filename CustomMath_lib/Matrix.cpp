//
// Created by Tiankai Ma on 2023/10/5.
//

#include "Matrix.h"

Matrix::Matrix() {
    this->rows = 0;
    this->cols = 0;
    this->matrix = std::vector<std::vector<long double>>(0, std::vector<long double>(0, 0));
}

Matrix::Matrix(unsigned long rows, unsigned long int cols) {
    // Frankly you shouldn't use this, but why not?
    this->rows = rows;
    this->cols = cols;
    this->matrix = std::vector<std::vector<long double>>(rows, std::vector<long double>(cols, 0));
}

Matrix::Matrix(std::vector<std::vector<long double>> matrix) {
    this->rows = matrix.size();
    this->cols = matrix[0].size();
    this->matrix = matrix;
}

Matrix::Matrix(std::string matlab_matrix) {
    // Testing purpose only, can ignore speed or memory efficiency
    std::vector<std::vector<long double>> result;
    std::vector<long double> row;
    for (int i = 0; i < matlab_matrix.size(); i++) {
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

Matrix Matrix::identity(unsigned long n) {
    auto result = Matrix(n, n);
    for (int i = 0; i < n; i++) {
        result.matrix[i][i] = 1;
    }
    return result;
}

void Matrix::print() {
    std::cout << "[";
    for (int i = 0; i < this->rows; i++) {
        std::cout << "[";
        for (int j = 0; j < this->cols; j++) {
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
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
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
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
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
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            for (int k = 0; k < this->cols; k++) {
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
    for (int i = 0; i < this->cols; i++) {
        for (int j = 0; j < this->rows; j++) {
            result.matrix[i][j] = this->matrix[j][i];
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) {
    auto result = Matrix(this->rows, this->cols);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
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
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result.matrix[i][j] = this->matrix[i][j] / scalar;
        }
    }
    return result;
}

Array Matrix::operator*(const Array &other) {
    if (this->cols != other.size) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
    auto result = Array(this->rows);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < other.size; j++) {
            result.array[i] += this->matrix[i][j] * other.array[j];
        }
    }
    return result;
}

Array Array::operator*(const Matrix &other) {
    if (this->size != other.rows) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
    auto result = Array(other.cols);
    for (int i = 0; i < other.cols; i++) {
        for (int j = 0; j < this->size; j++) {
            result.array[i] += this->array[j] * other.matrix[j][i];
        }
    }
    return result;
}

bool cmp(long double a, long double b) {
    return std::fabs(a - b) < 1e-6;
}

bool Matrix::operator==(const Matrix &other) const {
    if (this->rows != other.rows || this->cols != other.cols) {
        return false;
    }
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
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

void Matrix::requireSquare() const {
    if (!this->isSquare()) {
        throw std::invalid_argument("Matrix is not square.");
    }
}

Matrix Matrix::product(const Array &array1, const Array &array2) {
    auto result = Matrix(array1.size, array2.size);
    for (int i = 0; i < array1.size; i++) {
        for (int j = 0; j < array2.size; j++) {
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
