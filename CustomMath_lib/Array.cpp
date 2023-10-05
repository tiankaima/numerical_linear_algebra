//
// Created by Tiankai Ma on 2023/10/5.
//

#include <iostream>
#include <vector>
#include <string>
#include "Array.h"

Array::Array() {
    this->size = 0;
    this->array = std::vector<double>(0, 0);
}

Array::Array(int size) {
    this->size = size;
    this->array = std::vector<double>(size, 0);
}

Array::Array(std::vector<double> array) {
    this->size = array.size();
    this->array = array;
}

Array::Array(std::string matlab_array) {
    // Testing purpose only, can ignore speed or memory efficiency
    std::vector<double> result;
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
    std::vector<double> result(this->size, 0);
    for (int i = 0; i < this->size; i++) {
        result[i] = this->array[i] + other.array[i];
    }
    return Array(result);
}

Array Array::operator-(const Array &other) {
    if (this->size != other.size) {
        throw std::invalid_argument("Array dimensions must agree.");
    }
    std::vector<double> result(this->size, 0);
    for (int i = 0; i < this->size; i++) {
        result[i] = this->array[i] - other.array[i];
    }
    return Array(result);
}

Array Array::operator*(double scalar) {
    std::vector<double> result(this->size, 0);
    for (int i = 0; i < this->size; i++) {
        result[i] = this->array[i] * scalar;
    }
    return Array(result);
}

Array Array::operator/(double scalar) {
    std::vector<double> result(this->size, 0);
    for (int i = 0; i < this->size; i++) {
        result[i] = this->array[i] / scalar;
    }
    return Array(result);
}

double Array::operator*(const Array &other) {
    if (this->size != other.size) {
        throw std::invalid_argument("Array dimensions must agree.");
    }
    double result = 0;
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