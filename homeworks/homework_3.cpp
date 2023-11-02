//
// Created by tiankaima on 23-11-2.
//

#include "homework_3.h"

#define TEST_START auto start = std::chrono::high_resolution_clock::now();

#ifdef DEBUG
#define TEST_END(name) auto end = std::chrono::high_resolution_clock::now(); \
                 auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); \
                 std::cout << std::setw(30) << std::left << #name; \
                 x.print(); \
                 std::cout << std::setw(30) << std::left << #name \
                           << "diff = " << std::setw(30) << std::left  << (x - x_base).norm() \
                           << "time = " << std::setw(8) << std::left << duration.count() << " ms" << std::endl;
#else
#define TEST_END(name) auto end = std::chrono::high_resolution_clock::now(); \
                 auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); \
                 std::cout << std::setw(30) << std::left << #name \
                           << "diff = " << std::setw(30) << std::left  << (x - x_base).norm() \
                           << "time = " << std::setw(8) << std::left << duration.count() << " ms" << std::endl;
#endif

#define TEST_FUNCTION(A_func, b_func, x_base_func, function) { \
auto A = A_func(); \
auto x = b_func(); \
auto x_base = x_base_func(); \
TEST_START \
function(A, x); \
TEST_END(function) \
}

#define RUN_EVERY_TEST(group_name, A_func, b_func, x_base_func) \
    std::cout << std::endl << "######  " << #group_name << "  ######" << std::endl; \
    TEST_FUNCTION(A_func, b_func, x_base_func, LU_Solve_InPlace) \
    TEST_FUNCTION(A_func, b_func, x_base_func, LU_FP_Solve_InPlace) \
    TEST_FUNCTION(A_func, b_func, x_base_func, LU_PP_Solve_InPlace) \
    TEST_FUNCTION(A_func, b_func, x_base_func, Cholesky_Solve_InPlace) \
    TEST_FUNCTION(A_func, b_func, x_base_func, Cholesky_LDLT_Solve_InPlace) \
    TEST_FUNCTION(A_func, b_func, x_base_func, QR_Solve_InPlace)

void part_1() {
    RUN_EVERY_TEST(Q1, A_1, b_1, x_1)
    RUN_EVERY_TEST(Q2, A_2, b_2, x_2)
    RUN_EVERY_TEST(Q3, A_3, b_3, x_3)
}

int homework_3() {
    part_1();
    return 0;
}