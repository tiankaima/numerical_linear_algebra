//
// Created by Tiankai Ma on 2023/10/5.
//

#include "Array.h"

Array::Array() {
    this->size = 0;
    this->array = std::vector<long double>(0, 0);
}

Array::Array(unsigned int size) {
    this->size = size;
    this->array = std::vector<long double>(size, 0);
}

Array::Array(const std::vector<long double> &array) {
    this->size = array.size();
    this->array = array;
}

Array::Array(std::string matlab_array) {
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

void Array::print() {
    std::cout << "[";
    for (int i = 0; i < this->size; i++) {
        std::cout << this->array[i];
        if (i != this->size - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
}

Array Array::operator+(const Array &other) {
    if (this->size != other.size) {
        throw std::invalid_argument("Array dimensions must agree.");
    }
    auto result = Array(this->size);
    for (int i = 0; i < this->size; i++) {
        result.array[i] = this->array[i] + other.array[i];
    }
    return result;
}

Array Array::operator-(const Array &other) {
    if (this->size != other.size) {
        throw std::invalid_argument("Array dimensions must agree.");
    }
    auto result = Array(this->size);
    for (int i = 0; i < this->size; i++) {
        result.array[i] = this->array[i] - other.array[i];
    }
    return result;
}

Array Array::operator*(long double scalar) {
    auto result = Array(this->size);
    for (int i = 0; i < this->size; i++) {
        result.array[i] = this->array[i] * scalar;
    }
    return result;
}

Array Array::operator/(long double scalar) {
    auto result = Array(this->size);
    for (int i = 0; i < this->size; i++) {
        result.array[i] = this->array[i] / scalar;
    }
    return result;
}

long double Array::operator*(const Array &other) {
    if (this->size != other.size) {
        throw std::invalid_argument("Array dimensions must agree.");
    }
    long double result = 0;
    for (int i = 0; i < this->size; i++) {
        result += this->array[i] * other.array[i];
    }
    return result;
}

bool Array::operator==(const Array &other) const {
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

long double Array::norm() const {
    long double result = 0;
    for (int i = 0; i < this->size; i++) {
        result += this->array[i] * this->array[i];
    }
    return std::sqrt(result);
}

Array::Array(const Array &other) {
    this->size = other.size;
    this->array = other.array;
}
