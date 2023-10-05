//
// Created by Tiankai Ma on 2023/10/5.
//

#include <iostream>
#include "Matrix.h"
#include "Array.h"
#include <string>
#include <cmath>

Matrix::Matrix() {
    this->rows = 0;
    this->cols = 0;
    this->matrix = std::vector<std::vector<double>>(0, std::vector<double>(0, 0));
}

Matrix::Matrix(unsigned long rows, unsigned long int cols) {
    // Frankly you shouldn't use this, but why not?
    this->rows = rows;
    this->cols = cols;
    this->matrix = std::vector<std::vector<double>>(rows, std::vector<double>(cols, 0));
}

Matrix::Matrix(std::vector<std::vector<double>> matrix) {
    this->rows = matrix.size();
    this->cols = matrix[0].size();
    this->matrix = matrix;
}

Matrix::Matrix(std::string matlab_matrix) {
    // Testing purpose only, can ignore speed or memory efficiency
    std::vector<std::vector<double>> result;
    std::vector<double> row;
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
    std::vector<std::vector<double>> result(n, std::vector<double>(n, 0));
    for (int i = 0; i < n; i++) {
        result[i][i] = 1;
    }
    return Matrix(result);
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
    std::vector<std::vector<double>> result(this->rows, std::vector<double>(this->cols, 0));
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result[i][j] = this->matrix[i][j] + other.matrix[i][j];
        }
    }
    return Matrix(result);
}

Matrix Matrix::operator-(const Matrix &other) {
    if (this->rows != other.rows || this->cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
    std::vector<std::vector<double>> result(this->rows, std::vector<double>(this->cols, 0));
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result[i][j] = this->matrix[i][j] - other.matrix[i][j];
        }
    }
    return Matrix(result);
}

Matrix Matrix::operator*(const Matrix &other) {
    if (this->cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
    std::vector<std::vector<double>> result(this->rows, std::vector<double>(other.cols, 0));
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            for (int k = 0; k < this->cols; k++) {
                result[i][j] += this->matrix[i][k] * other.matrix[k][j];
            }
        }
    }
    return Matrix(result);
}

Matrix Matrix::transpose() {
    std::vector<std::vector<double>> result(this->cols, std::vector<double>(this->rows, 0));
    for (int i = 0; i < this->cols; i++) {
        for (int j = 0; j < this->rows; j++) {
            result[i][j] = this->matrix[j][i];
        }
    }
    return Matrix(result);
}

Matrix Matrix::operator*(double scalar) {
    std::vector<std::vector<double>> result(this->rows, std::vector<double>(this->cols, 0));
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result[i][j] = this->matrix[i][j] * scalar;
        }
    }
    return Matrix(result);
}

Matrix Matrix::operator/(double scalar) {
    if (scalar == 0) {
        throw std::invalid_argument("Cannot divide by zero.");
    }
    std::vector<std::vector<double>> result(this->rows, std::vector<double>(this->cols, 0));
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            result[i][j] = this->matrix[i][j] / scalar;
        }
    }
    return Matrix(result);
}

Array Matrix::operator*(const Array &other) {
    if (this->cols != other.size) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
    std::vector<double> result(this->rows, 0);
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < other.size; j++) {
            result[i] += this->matrix[i][j] * other.array[j];
        }
    }
    return Array(result);
}

Array Array::operator*(const Matrix &other) {
    if (this->size != other.rows) {
        throw std::invalid_argument("Matrix dimensions must agree.");
    }
    std::vector<double> result(other.cols, 0);
    for (int i = 0; i < other.cols; i++) {
        for (int j = 0; j < this->size; j++) {
            result[i] += this->array[j] * other.matrix[j][i];
        }
    }
    return Array(result);
}

bool cmp(double a, double b) {
    return fabs(a - b) < 1e-6;
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
    std::vector<std::vector<double>> result(array1.size, std::vector<double>(array2.size, 0));
    for (int i = 0; i < array1.size; i++) {
        for (int j = 0; j < array2.size; j++) {
            result[i][j] = array1.array[i] * array2.array[j];
        }
    }
    return Matrix(result);
}