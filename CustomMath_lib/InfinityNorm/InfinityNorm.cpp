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

lld MatrixNorm_1(const Matrix &A) {
    Vector x = Vector(A.cols);
    for (int i = 0; i < A.cols; i++) {
        x.array[i] = 1;
    }
    while (true) {
        Vector w = A * x;
        Vector v = sign(w);
        Vector z = A.transpose() * v;

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