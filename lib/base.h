//
// Created by TianKai Ma on 2023/12/15.
//

#ifndef NUMERICAL_ALGEBRA_BASE_H
#define NUMERICAL_ALGEBRA_BASE_H

#define ENABLE_TIMING
#define ITERATION_METHOD_MAX_ITERATION 100000

#include "iostream"
#include "iomanip"
#include "cmath"
#include "vector"
#include "string"
#include "random"
#include "chrono"
#include "optional"
#include "algorithm"

#define ull unsigned long long
#define lld long double

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define SIGN(a) ((a) > 0 ? 1 : ((a) < 0 ? -1 : 0))

bool cmp(lld a, lld b);

template<typename T>
struct IterationMethodOutput {
    T result;
    int iteration_count;
    std::chrono::microseconds time_cost;
};

#ifdef ENABLE_TIMING
#define TIMING_START auto start = std::chrono::high_resolution_clock::now();
#define TIMING_END auto end = std::chrono::high_resolution_clock::now();
#define TIMING_RETURN_DURATION std::chrono::duration_cast<std::chrono::microseconds>(end - start)
#else
#define TIMING_START
#define TIMING_END
#define TIMING_RETURN_DURATION std::chrono::microseconds(0)
#endif

#endif //NUMERICAL_ALGEBRA_BASE_H
