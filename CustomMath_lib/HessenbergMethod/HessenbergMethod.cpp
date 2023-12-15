//
// Created by TianKai Ma on 2023/12/14.
//

#include "HessenbergMethod.h"

void HessenbergMethod_Inplace(Matrix &A) {
    auto n = A.rows;
    Vector v;
    lld beta;

    for (ull k = 0; k < n - 1; k++) {
        auto x = Vector(n - k - 1);
        for (ull i = 0; i < n - k - 1; i++) {
            x.array[i] = A.matrix[k + i + 1][k];
        }
        HouseHolderMethod(x, v, beta);

        auto w = product(v, v) * beta;

        auto A_sub = A.sub_matrix(k + 1, n, k, n);
        A_sub = A_sub - w * A_sub;
        A.set(k + 1, n, k, n, A_sub);

        A_sub = A.sub_matrix(0, n, k + 1, n);
        A_sub = A_sub - A_sub * w;
        A.set(0, n, k + 1, n, A_sub);
    }
}

void HessenbergMethod_Inplace(Matrix &A, Matrix &P) {
    // init P here:
    P = Matrix::identity(A.rows);

    auto n = A.rows;
    Vector v;
    lld beta;

    for (ull k = 0; k < n - 1; k++) {
        auto x = Vector(n - k - 1);
        for (ull i = 0; i < n - k - 1; i++) {
            x.array[i] = A.matrix[k + i + 1][k];
        }
        HouseHolderMethod(x, v, beta);

        auto w = product(v, v) * beta;

        auto A_sub = A.sub_matrix(k + 1, n, k, n);
        A_sub = A_sub - w * A_sub;
        A.set(k + 1, n, k, n, A_sub);

        A_sub = A.sub_matrix(0, n, k + 1, n);
        A_sub = A_sub - A_sub * w;
        A.set(0, n, k + 1, n, A_sub);

        auto U_sub = P.sub_matrix(k + 1, n, 0, n);
        U_sub = U_sub - w * U_sub;
        P.set(k + 1, n, 0, n, U_sub);
    }
}

HessenbergMethod_Result HessenbergMethod(const Matrix &A) {
    auto result = A;
    Matrix P;
    HessenbergMethod_Inplace(result, P);
    return {result.clean(), P.clean()}; // clean the matrix
}

Matrix HessenbergMethod(const Matrix &A, Matrix &P) {
    auto result = A;
    HessenbergMethod_Inplace(result, P);
    return result.clean(); // clean the matrix
}