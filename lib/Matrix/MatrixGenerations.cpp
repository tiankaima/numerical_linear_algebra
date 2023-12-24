//
// Created by TianKai Ma on 2023/12/15.
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

Matrix::Matrix(ull rows, ull cols, lld default_value) {
    this->rows = rows;
    this->cols = cols;
    this->matrix = std::vector<std::vector<lld>>(rows, std::vector<lld>(cols, default_value));
}

Matrix::Matrix(ull rows, ull cols, double lower_bound, double upper_bound) {
    // generate a matrix with random values in range [lower_bound, upper_bound]
    this->rows = rows;
    this->cols = cols;
    this->matrix = std::vector<std::vector<lld>>(rows, std::vector<lld>(cols, 0));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(lower_bound, upper_bound);
    for (ull i = 0; i < rows; i++) {
        for (ull j = 0; j < cols; j++) {
            this->matrix[i][j] = dis(gen);
        }
    }
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


Matrix Matrix::hilbert(ull n) {
    auto result = Matrix(n, n);
    for (ull i = 0; i < n; i++) {
        for (ull j = 0; j < n; j++) {
            result.matrix[i][j] = 1.0 / (lld) (i + j + 1);
        }
    }
    return result;
}

Matrix Matrix::UpperTriangular(ull n, lld default_value) {
    auto result = Matrix(n, n);
    for (ull i = 0; i < n; i++) {
        for (ull j = i; j < n; j++) {
            result.matrix[i][j] = default_value;
        }
    }
    return result;
}

Matrix Matrix::LowerTriangular(ull n, lld default_value) {
    auto result = Matrix(n, n);
    for (ull i = 0; i < n; i++) {
        for (ull j = 0; j <= i; j++) {
            result.matrix[i][j] = default_value;
        }
    }
    return result;
}

Matrix Matrix::Diagonal(ull n, lld default_value) {
    auto result = Matrix(n, n);
    for (ull i = 0; i < n; i++) {
        result.matrix[i][i] = default_value;
    }
    return result;
}

Matrix::Matrix(const Matrix &other) {
    this->rows = other.rows;
    this->cols = other.cols;
    this->matrix = other.matrix;
}
