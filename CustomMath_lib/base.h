//
// Created by TianKai Ma on 2023/12/15.
//

#ifndef NUMERICAL_ALGEBRA_BASE_H
#define NUMERICAL_ALGEBRA_BASE_H

#define ENABLE_ITERATION_METHOD_TIMING
#define ITERATION_METHOD_MAX_ITERATION 100000

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

#ifdef ENABLE_ITERATION_METHOD_TIMING
#define ITERATION_METHOD_TIMING_START auto start = std::chrono::high_resolution_clock::now();
#define ITERATION_METHOD_TIMING_END auto end = std::chrono::high_resolution_clock::now(); \
                  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
#define ITERATION_METHOD_RETURN_DURATION duration
#else
#define ITERATION_METHOD_TIMING_START
#define ITERATION_METHOD_TIMING_END
#define ITERATION_METHOD_RETURN_DURATION std::chrono::microseconds(0)
#endif

#endif //NUMERICAL_ALGEBRA_BASE_H
