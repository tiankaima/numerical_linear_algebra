//
// Created by TianKai Ma on 2023/12/14.
//

#ifndef NUMERICAL_ALGEBRA_HESSENBERGMETHOD_H
#define NUMERICAL_ALGEBRA_HESSENBERGMETHOD_H

#include "CustomMath_lib.h"

typedef struct {
    Matrix H;
    Matrix P;
} HessenbergMethod_Result;

/// P^T A P = H, returns H, P
HessenbergMethod_Result HessenbergMethod(const Matrix &A);

/// P^T A P = H, inplace returns H only, P passed in
void HessenbergMethod_Inplace(Matrix &A, Matrix &P);

#endif //NUMERICAL_ALGEBRA_HESSENBERGMETHOD_H
