//
// Created by TianKai Ma on 2023/12/14.
//

#ifndef NUMERICAL_ALGEBRA_HESSENBERGMETHOD_H
#define NUMERICAL_ALGEBRA_HESSENBERGMETHOD_H

#include "Matrix/Matrix.h"
#include "Vector/Vector.h"
#include "HouseholderMethod/HouseholderMethod.h"

void HessenbergMethod_Inplace(Matrix &A);

Matrix HessenbergMethod(const Matrix &A);

void HessenbergMethod_Inplace(Matrix &A, Matrix &U);

Matrix HessenbergMethod(const Matrix &A, Matrix &U);

#endif //NUMERICAL_ALGEBRA_HESSENBERGMETHOD_H
