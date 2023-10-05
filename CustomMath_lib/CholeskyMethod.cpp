//
// Created by tiankaima on 23-10-5.
//

#include "CholeskyMethod.h"
#include "iostream"
#include <cmath>

//void CholeskyFactorization(const Matrix &A, Matrix *L);
void CholeskyFactorization_T(Matrix *A) {
    if (A->rows != A->cols) {
        throw std::invalid_argument("A is not a square matrix");
    }

    for (int k = 0; k < A->rows; k++) {
        if (A->matrix[k][k] <= 0) {
            throw std::invalid_argument("A is not a positive definite matrix");
        }
        A->matrix[k][k] = sqrt(A->matrix[k][k]);
        for (int i = k + 1; i < A->rows; i++) {
            A->matrix[i][k] /= A->matrix[k][k];
        }
        for (int j = k + 1; j < A->rows; j++) {
            for (int i = j; i < A->rows; i++) {
                A->matrix[i][j] -= A->matrix[i][k] * A->matrix[j][k];
            }
        }
    }
}

// 1.3.2
//void Cholesky_LDLT_Factorization(const Matrix &A, Matrix *L, Matrix *D);
//void Cholesky_LDLT_Factorization_T(Matrix *A, Matrix *D);

