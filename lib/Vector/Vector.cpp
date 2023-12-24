//
// Created by Tiankai Ma on 2023/10/5.
//

#include "Vector.h"

Vector::Vector() {
    this->size = 0;
    this->array = std::vector<lld>(0, 0);
}

Vector::Vector(ull size) {
    this->size = size;
    this->array = std::vector<lld>(size, 0);
}


Vector::Vector(ull size, lld default_value) {
    this->size = size;
    this->array = std::vector<lld>(size, default_value);
}

Vector::Vector(ull size, double lower_bound, double upper_bound) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(lower_bound, upper_bound);
    std::vector<lld> result = std::vector<lld>(size);
    for (int i = 0; i < size; i++) {
        result[i] = dis(gen);
    }
    this->size = size;
    this->array = result;
}

Vector::Vector(const std::vector<lld> &array) {
    this->size = array.size();
    this->array = array;
}

Vector::Vector(std::string matlab_array) {
    // Testing purpose only, can ignore speed or memory efficiency
    std::vector<lld> result;
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

Vector Vector::sub_vector(ull start, ull end) const {
#ifdef DEBUG
    if (end > this->size || start > end) {
        throw std::invalid_argument("Invalid sub_vector range.");
    }
#endif

    std::vector<lld> result;
    for (ull i = start; i < end; i++) {
        result.push_back(this->array[i]);
    }
    return Vector(result);
}

void Vector::set(ull start, ull end, const Vector &other) {
#ifdef DEBUG
    if (end > this->size || start > end) {
        throw std::invalid_argument("Invalid sub_vector range.");
    }
    if (other.size != end - start) {
        throw std::invalid_argument("Invalid sub_vector size.");
    }
#endif

    for (ull i = start; i < end; i++) {
        this->array[i] = other.array[i - start];
    }
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

Vector Vector::operator+(const Vector &other) const {
#ifdef DEBUG
    if (this->size != other.size) {
        throw std::invalid_argument("Vector dimensions must agree.");
    }
#endif

    auto result = Vector(this->size);
    for (int i = 0; i < this->size; i++) {
        result.array[i] = this->array[i] + other.array[i];
    }
    return result;
}

Vector Vector::operator-(const Vector &other) const {
#ifdef DEBUG
    if (this->size != other.size) {
        throw std::invalid_argument("Vector dimensions must agree.");
    }
#endif

    auto result = Vector(this->size);
    for (int i = 0; i < this->size; i++) {
        result.array[i] = this->array[i] - other.array[i];
    }
    return result;
}

Vector Vector::operator*(lld scalar) const {
    auto result = Vector(this->size);
    for (int i = 0; i < this->size; i++) {
        result.array[i] = this->array[i] * scalar;
    }
    return result;
}

Vector Vector::operator/(lld scalar) const {
    auto result = Vector(this->size);
    for (int i = 0; i < this->size; i++) {
        result.array[i] = this->array[i] / scalar;
    }
    return result;
}

lld Vector::operator*(const Vector &other) const {
#ifdef DEBUG
    if (this->size != other.size) {
        throw std::invalid_argument("Vector dimensions must agree.");
    }
#endif

    lld result = 0;
    for (int i = 0; i < this->size; i++) {
        result += this->array[i] * other.array[i];
    }
    return result;
}

Vector operator*(lld scalar, const Vector &vector) {
    return vector * scalar;
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

lld Vector::norm() const {
    lld result = 0;
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