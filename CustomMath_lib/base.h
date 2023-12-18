//
// Created by TianKai Ma on 2023/12/15.
//

#ifndef NUMERICAL_ALGEBRA_BASE_H
#define NUMERICAL_ALGEBRA_BASE_H

#include "iostream"
#include "iomanip"
#include "cmath"
#include "vector"
#include "string"
#include "random"
#include "chrono"

#define ull unsigned long long
#define lld long double

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

bool cmp(lld a, lld b);

template<typename T>
struct IterationMethodOutput {
    T result;
    int iteration_count;
    std::chrono::microseconds time_cost;
};

#endif //NUMERICAL_ALGEBRA_BASE_H
