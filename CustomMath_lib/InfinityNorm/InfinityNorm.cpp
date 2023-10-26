//
// Created by tiankaima on 23-10-24.
//

#include "InfinityNorm.h"

lld MatrixNorm_Infinity(const Matrix &A) {
    lld max = 0;
    for (int i = 0; i < A.rows; i++) {
        lld sum = 0;
        for (int j = 0; j < A.cols; j++) {
            sum += std::abs(A.matrix[i][j]);
        }
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}

lld VectorNorm_Infinity(const Vector &x) {
    lld max = 0;
    for (int i = 0; i < x.size; i++) {
        if (std::abs(x.array[i]) > max) {
            max = std::abs(x.array[i]);
        }
    }
    return max;
}

lld MatrixNorm_1(const Matrix &B) {
    Vector x = Vector(B.cols);
    for (int i = 0; i < B.cols; i++) {
        x.array[i] = 1;
    }
    while (true) {
        Vector w = B * x;
        Vector v = sign(w);
        Vector z = B.transpose() * v;

        ull max_pos = 0;
        lld max = 0;
        for (ull i = 0; i < z.size; i++) {
            if (std::abs(z.array[i]) > max) {
                max = std::abs(z.array[i]);
                max_pos = i;
            }
        }

        if (max <= z * x) {
            return max;
        } else {
            x = Vector(B.cols);
            x.array[max_pos] = 1;
        }
    }
}

lld MatrixNorm_A_Inv_T_1(const Matrix &A) {
    // this calculates norm 1 of A^(-T)
    Vector x = Vector(A.cols);
    for (int i = 0; i < A.cols; i++) {
        x.array[i] = 1;
    }

    while (true) {
        // TODO: This isn't really optimized since we don't need to calculate A^(-T) every time
        Vector w = LU_PP_Solve(A.transpose(), x);
        Vector v = sign(w);
        Vector z = LU_PP_Solve(A, v);

        ull max_pos = 0;
        lld max = 0;
        for (ull i = 0; i < z.size; i++) {
            if (std::abs(z.array[i]) > max) {
                max = std::abs(z.array[i]);
                max_pos = i;
            }
        }

        if (max <= z * x) {
            return max;
        } else {
            x = Vector(A.cols);
            x.array[max_pos] = 1;
        }
    }
}