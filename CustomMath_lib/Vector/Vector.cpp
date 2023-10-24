//
// Created by Tiankai Ma on 2023/10/5.
//

#include "Vector.h"

Vector::Vector() {
    this->size = 0;
    this->array = std::vector<long double>(0, 0);
}

Vector::Vector(unsigned int size) {
    this->size = size;
    this->array = std::vector<long double>(size, 0);
}

Vector::Vector(const std::vector<long double> &array) {
    this->size = array.size();
    this->array = array;
}

Vector::Vector(std::string matlab_array) {
    // Testing purpose only, can ignore speed or memory efficiency
    std::vector<long double> result;
    for (int i = 0; i < matlab_array.size(); i++) {
        if (matlab_array[i] == '[' || matlab_array[i] == ' ') {
            continue;
        } else if (matlab_array[i] == ']') {
            break;
        } else {
            std::string number;
            while (matlab_array[i] != ' ' && matlab_array[i] != ';' && matlab_array[i] != ']') {
                number += matlab_array[i];
                i++;
            }
            result.push_back(std::stod(number));
            i--;
        }
    }
    this->size = result.size();
    this->array = result;
}

void Vector::print() {
    std::cout << "[";
    for (int i = 0; i < this->size; i++) {
        std::cout << this->array[i];
        if (i != this->size - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
}

Vector Vector::operator+(const Vector &other) {
    if (this->size != other.size) {
        throw std::invalid_argument("Vector dimensions must agree.");
    }
    auto result = Vector(this->size);
    for (int i = 0; i < this->size; i++) {
        result.array[i] = this->array[i] + other.array[i];
    }
    return result;
}

Vector Vector::operator-(const Vector &other) {
    if (this->size != other.size) {
        throw std::invalid_argument("Vector dimensions must agree.");
    }
    auto result = Vector(this->size);
    for (int i = 0; i < this->size; i++) {
        result.array[i] = this->array[i] - other.array[i];
    }
    return result;
}

Vector Vector::operator*(long double scalar) {
    auto result = Vector(this->size);
    for (int i = 0; i < this->size; i++) {
        result.array[i] = this->array[i] * scalar;
    }
    return result;
}

Vector Vector::operator/(long double scalar) {
    auto result = Vector(this->size);
    for (int i = 0; i < this->size; i++) {
        result.array[i] = this->array[i] / scalar;
    }
    return result;
}

long double Vector::operator*(const Vector &other) {
    if (this->size != other.size) {
        throw std::invalid_argument("Vector dimensions must agree.");
    }
    long double result = 0;
    for (int i = 0; i < this->size; i++) {
        result += this->array[i] * other.array[i];
    }
    return result;
}

bool Vector::operator==(const Vector &other) const {
    if (this->size != other.size) {
        return false;
    }
    for (int i = 0; i < this->size; i++) {
        if (this->array[i] != other.array[i]) {
            return false;
        }
    }
    return true;
}

long double Vector::norm() const {
    long double result = 0;
    for (int i = 0; i < this->size; i++) {
        result += this->array[i] * this->array[i];
    }
    return std::sqrt(result);
}

Vector::Vector(const Vector &other) {
    this->size = other.size;
    this->array = other.array;
}

Vector sign(const Vector &vector) {
    Vector result = Vector(vector.size);
    for (int i = 0; i < vector.size; i++) {
        if (vector.array[i] > 0) {
            result.array[i] = 1;
        } else if (vector.array[i] < 0) {
            result.array[i] = -1;
        } else {
            result.array[i] = 0;
        }
    }
    return result;
}