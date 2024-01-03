//
// Created by Tiankai Ma on 2023/10/5.
//

#include "Matrix.h"

#define HIDE_ZERO_IN_MATRIX_PRINT 1

void Matrix::print() {
    std::cout << std::fixed << std::setprecision(6);

    std::cout << "[";
    for (ull i = 0; i < this->rows; i++) {
        std::cout << "[";
        for (ull j = 0; j < this->cols; j++) {
            if (std::abs(this->matrix[i][j]) < 1e-10 && HIDE_ZERO_IN_MATRIX_PRINT) {
                std::cout << "\t" << "        " << "\t";
            } else {
                std::cout << "\t" << this->matrix[i][j] << "\t";
            }
        }
        std::cout << "]";
        if (i != this->rows - 1) {
            std::cout << "," << std::endl;
        }
    }
    std::cout << "]" << std::endl;
}

Matrix Matrix::clean(lld eps) const {
    auto result = Matrix(this->rows, this->cols);
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < this->cols; j++) {
            if (std::abs(this->matrix[i][j]) < eps) {
                result.matrix[i][j] = 0;
            } else {
                result.matrix[i][j] = this->matrix[i][j];
            }
        }
    }
    return result;
}

Matrix Matrix::transpose() const {
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

Matrix Matrix::diagonal_inverse() const {
#ifdef DEBUG
    if (!this->isSquare()) {
        throw std::invalid_argument("Matrix must be square.");
    }
#endif

    auto result = Matrix(this->rows, this->cols);
    for (ull i = 0; i < this->rows; i++) {
        result.matrix[i][i] = 1.0 / this->matrix[i][i];
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

lld Matrix::norm() const {
    lld result = 0;
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < this->cols; j++) {
            result += this->matrix[i][j] * this->matrix[i][j];
        }
    }
    return std::sqrt(result);
}

lld Matrix::min() const {
    lld result = this->matrix[0][0];
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < this->cols; j++) {
            result = std::min(result, this->matrix[i][j]);
        }
    }
    return result;
}

lld Matrix::max() const {
    lld result = this->matrix[0][0];
    for (ull i = 0; i < this->rows; i++) {
        for (ull j = 0; j < this->cols; j++) {
            result = std::max(result, this->matrix[i][j]);
        }
    }
    return result;
}
