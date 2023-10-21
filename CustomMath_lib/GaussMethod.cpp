//
// Created by tiankaima on 23-10-5.
//

#include "GaussMethod.h"

Array LowerGaussSolve(const Matrix &A, const Array &b) {
    auto x = Array(b);
    LowerGaussSolve_T(A, x);
    return x;
}

void LowerGaussSolve_T(const Matrix &A, Array &b) {
    A.requireSquare();

    for (unsigned int i = 0; i < b.size; i++) {
        b.array[i] = b.array[i] / A.matrix[i][i];
        for (unsigned int j = i + 1; j < b.size; j++) {
            b.array[j] -= A.matrix[j][i] * b.array[i];
        }
    }
}

Array UpperGaussSolve(const Matrix &A, const Array &b) {
    auto x = Array(b);
    UpperGaussSolve_T(A, x);
    return x;
}

void UpperGaussSolve_T(const Matrix &A, Array &b) {
    A.requireSquare();

    for (unsigned int i = b.size - 1; i != -1; i--) {
        b.array[i] = b.array[i] / A.matrix[i][i];
        for (unsigned int j = i - 1; j != -1; j--) {
            b.array[j] -= A.matrix[j][i] * b.array[i];
        }
    }
}

Array LU_Solve(const Matrix &A, const Array &b) {
    Matrix L, U;
    LU_Factorization(A, &L, &U);
    Array y = LowerGaussSolve(L, b);
    Array x = UpperGaussSolve(U, y);
    return x;
}

void LU_Factorization_T(Matrix *A) {
    A->requireSquare();

    for (int i = 0; i < A->rows - 1; i++) {
        for (int j = i + 1; j < A->rows; j++) {
            A->matrix[j][i] /= A->matrix[i][i];
            for (int k = i + 1; k < A->rows; k++) {
                A->matrix[j][k] -= A->matrix[j][i] * A->matrix[i][k];
            }
        }
    }
}

void LU_Factorization(const Matrix &A, Matrix *L, Matrix *U) {
    A.requireSquare();

    *U = Matrix(A);
    LU_Factorization_T(U);
    *L = Matrix(A.rows, A.cols);

    for (int i = 0; i < A.rows; i++) {
        L->matrix[i][i] = 1;
    }
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < i; j++) {
            L->matrix[i][j] = U->matrix[i][j];
            U->matrix[i][j] = 0;
        }
    }
}

Array LU_FP_Solve(const Matrix &A, const Array &b) {
    Matrix L, U, P, Q;
    LU_FP_Factorization(A, &L, &U, &P, &Q);
    Array Pb = P * b;
    Array UQix = LowerGaussSolve(L, Pb);
    Array Qix = UpperGaussSolve(U, UQix);
    Array x = Q * Qix;
    return x;
}

void LU_FP_Factorization_T(Matrix *A, Matrix *P, Matrix *Q) {
    A->requireSquare();

    // init P and Q
    *P = Matrix::identity(A->rows);
    *Q = Matrix::identity(A->rows);

    for (int i = 0; i < A->rows; i++) {
        // find the pivot
        int pivot_i = i, pivot_j = i;
        long double pivot = std::abs(A->matrix[i][i]);
        for (int j = i; j < A->rows; j++) {
            for (int k = i; k < A->rows; k++) {
                if (std::abs(A->matrix[j][k]) > std::abs(pivot)) {
                    pivot = A->matrix[j][k];
                    pivot_i = j;
                    pivot_j = k;
                }
            }
        }
        // swap rows
        if (pivot_i != i) {
            for (int j = 0; j < A->rows; j++) {
                std::swap(A->matrix[i][j], A->matrix[pivot_i][j]);
            }
        }
        // swap columns
        if (pivot_j != i) {
            for (int j = 0; j < A->rows; j++) {
                std::swap(A->matrix[j][i], A->matrix[j][pivot_j]);
            }
        }

        // construct P and Q
        std::swap(P->matrix[i], P->matrix[pivot_i]);
        std::swap(Q->matrix[i], Q->matrix[pivot_j]);

        if (pivot == 0) {
            throw std::invalid_argument("A is singular");
        }

        // do the elimination
        for (int j = i + 1; j < A->rows; j++) {
            A->matrix[j][i] /= A->matrix[i][i];
            for (int k = i + 1; k < A->rows; k++) {
                A->matrix[j][k] -= A->matrix[j][i] * A->matrix[i][k];
            }
        }
    }
}

void LU_FP_Factorization(const Matrix &A, Matrix *L, Matrix *U, Matrix *P, Matrix *Q) {
    A.requireSquare();

    *U = Matrix(A);
    LU_FP_Factorization_T(U, P, Q);
    *L = Matrix(A.rows, A.cols);

    for (int i = 0; i < A.rows; i++) {
        L->matrix[i][i] = 1;
    }
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < i; j++) {
            L->matrix[i][j] = U->matrix[i][j];
            U->matrix[i][j] = 0;
        }
    }
}

Array LU_PP_Solve(const Matrix &A, const Array &b) {
    Matrix L, U, P;
    LU_PP_Factorization(A, &L, &U, &P);
    Array Pb = P * b;
    Array y = LowerGaussSolve(L, Pb);
    Array x = UpperGaussSolve(U, y);
    return x;
}

void LU_PP_Factorization_T(Matrix *A, Matrix *P) {
    A->requireSquare();

    // init P
    *P = Matrix::identity(A->rows);

    for (int i = 0; i < A->rows; i++) {
        // find the pivot
        int pivot_i = i;
        long double pivot = std::abs(A->matrix[i][i]);
        for (int j = i; j < A->rows; j++) {
            if (std::abs(A->matrix[j][i]) > std::abs(pivot)) {
                pivot = A->matrix[j][i];
                pivot_i = j;
            }
        }
        // swap rows
        if (pivot_i != i) {
            for (int j = 0; j < A->rows; j++) {
                std::swap(A->matrix[i][j], A->matrix[pivot_i][j]);
            }
        }

        // construct P
        std::swap(P->matrix[i], P->matrix[pivot_i]);

        if (pivot == 0) {
            throw std::invalid_argument("A is singular");
        }

        // do the elimination
        for (int j = i + 1; j < A->rows; j++) {
            A->matrix[j][i] /= A->matrix[i][i];
            for (int k = i + 1; k < A->rows; k++) {
                A->matrix[j][k] -= A->matrix[j][i] * A->matrix[i][k];
            }
        }
    }
}

void LU_PP_Factorization(const Matrix &A, Matrix *L, Matrix *U, Matrix *P) {
    A.requireSquare();

    *U = Matrix(A);
    LU_PP_Factorization_T(U, P);
    *L = Matrix(A.rows, A.cols);

    for (int i = 0; i < A.rows; i++) {
        L->matrix[i][i] = 1;
    }
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < i; j++) {
            L->matrix[i][j] = U->matrix[i][j];
            U->matrix[i][j] = 0;
        }
    }
}
