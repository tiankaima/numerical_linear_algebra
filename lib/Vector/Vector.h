//
// Created by Tiankai Ma on 2023/10/5.
//

#ifndef NUMERICAL_ALGEBRA_VECTOR_H
#define NUMERICAL_ALGEBRA_VECTOR_H

#include "base.h"

class Vector {
public:
    std::vector<lld> array;
    ull size;

    /// 0
    Vector();

    /// Copy constructor
    Vector(const Vector &other);

    /// size, 0
    explicit Vector(ull size);

    /// size, default_value
    explicit Vector(ull size, lld default_value);

    /// size, [lower_bound, upper_bound]
    explicit Vector(ull size, double lower_bound, double upper_bound);

    /// 1d vector
    explicit Vector(const std::vector<lld> &array);

    /// \warning this constructor is not robust / time-efficient
    explicit Vector(std::string matlab_array);

    /// Return a sub-vector of this vector [start, end)
    [[nodiscard]] Vector sub_vector(ull start, ull end) const;

    /// Set a sub-vector of this vector [start, end)
    /// \warning this is often used in conjunction with sub_vector()
    void set(ull start, ull end, const Vector &other);

    /// Print the vector
    void print();

    /// u == v
    [[nodiscard]] bool operator==(const Vector &other) const;

    /// 2-norm
    [[nodiscard]] lld norm() const;

    /// u + v
    [[nodiscard]] Vector operator+(const Vector &other) const;

    /// u - v
    [[nodiscard]] Vector operator-(const Vector &other) const;

    /// u * v -> Real
    [[nodiscard]] lld operator*(const Vector &other) const;

    /// u * scalar
    [[nodiscard]] Vector operator*(lld scalar) const;

    /// u / scalar
    [[nodiscard]] Vector operator/(lld scalar) const;
};

/// [1,2,3,0,2] -> [1,1,1,0,1]
Vector sign(const Vector &vector);

/// scalar * u
Vector operator*(lld scalar, const Vector &vector);

#endif //NUMERICAL_ALGEBRA_VECTOR_H
