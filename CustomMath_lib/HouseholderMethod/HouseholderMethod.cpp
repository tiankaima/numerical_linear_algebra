//
// Created by tiankaima on 23-11-2.
//

#include "HouseholderMethod.h"

void HouseHolderMethod(const Vector &x, Vector &v, lld &beta) {
    ull n = x.size;
    lld eng = VectorNorm_Infinity(x);
    Vector y = x / eng;
    lld sigma = y * y - y.array[0] * y.array[0];
    v = Vector(n);
    for (ull i = 1; i < n; i++) {
        v.array[i] = y.array[i];
    }
    v.array[0] = 1;
    if (sigma != 0) {
        lld alpha = std::sqrt(y.array[0] * y.array[0] + sigma);
        if (y.array[0] <= 0) {
            v.array[0] = y.array[0] - alpha;
        } else {
            v.array[0] = -sigma / (y.array[0] + alpha);
        }
        beta = 2 * v.array[0] * v.array[0] / (sigma + v.array[0] * v.array[0]);
        v = v / v.array[0];
    } else {
        beta = 0;
    }
}

void QRFactorization_InPlace(Matrix &A, Vector &d) {
    ull m = A.rows;
    ull n = A.cols;
    ull k = std::min(m, n);
    d = Vector(k);

    for (ull j = 0; j < k; j++) {
        Vector v;
        lld beta;
        auto A_j = Vector(m - j);
        for (ull i = j; i < m; i++) {
            A_j.array[i - j] = A.matrix[i][j];
        }
        HouseHolderMethod(A_j, v, beta);

        auto A_sub = A.sub_matrix(j, m, j, n);
//        A_sub = (Matrix::identity(m - j) - product(v, v) * beta) * A_sub;
        auto w = (A_sub.transpose() * v) * beta;
        A_sub = A_sub - product(v, w);
        A.set(j, m, j, n, A_sub);
        d.array[j] = beta;

        for (ull i = j + 1; i < m; i++) {
            A.matrix[i][j] = v.array[i - j];
        }
    }
}

void QRFactorization(const Matrix &A, Matrix &Q, Matrix &R) {
    ull m = A.rows;
    ull n = A.cols;
//    Q = Matrix(n, m);
    R = Matrix(n, n);

    auto B = Matrix(A);
    Vector d;
    QRFactorization_InPlace(B, d);

    // save r as upper triangular matrix
    for (ull i = 0; i < n; i++) {
        for (ull j = i; j < n; j++) {
            R.matrix[i][j] = B.matrix[i][j];
        }
    }

    // now _Q.
    auto _Q = Matrix::identity(m);

    // fixme: I'll admit the following way is terrible:
    auto v_list = std::vector<Vector>(n);
    for (ull i = 0; i < n; i++) {
        auto v = Vector(m);
        v.array[0] = 1;
        for (ull j = i + 1; j < m; j++) {
            v.array[j] = B.matrix[j][i];
        }
        auto w = (_Q.transpose() * v) * d.array[i];
        _Q = _Q - product(v, w);
    }
    _Q.print();

    // stripping _Q to n x m -> Q:
    Q = _Q.sub_matrix(0, n, 0, m);
}

void QR_Solve_InPlace(Matrix &A, Vector &b) {
    Vector d;
    auto v = Vector(A.rows);
    QRFactorization_InPlace(A, d);
//    for (ull i = A.cols - 1; i != -1; i--) {
    for (ull i = 0; i < A.cols; i++) {
        v = Vector(A.rows, 0);
        v.array[i] = 1;
        for (ull j = i + 1; j < A.rows; j++) {
            v.array[j] = A.matrix[j][i];
        }
        b = b - v * (v * b) * d.array[i];
    }
    UpperTriangleMatrix_Solve_InPlace(A.sub_matrix(0, A.cols, 0, A.cols), b);
}

Vector QR_Solve(const Matrix &A, const Vector &b) {
    auto A_copy = Matrix(A);
    auto b_copy = Vector(b);
    QR_Solve_InPlace(A_copy, b_copy);
    return b_copy.sub_vector(0, A.cols);
}