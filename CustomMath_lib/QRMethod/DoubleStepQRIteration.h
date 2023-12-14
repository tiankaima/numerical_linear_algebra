//
// Created by TianKai Ma on 2023/12/14.
//

#ifndef NUMERICAL_ALGEBRA_DOUBLESTEPQRITERATION_H
#define NUMERICAL_ALGEBRA_DOUBLESTEPQRITERATION_H

#include "Matrix/Matrix.h"
#include "Vector/Vector.h"
#include "HouseholderMethod/HouseholderMethod.h"
#include "HouseholderMethod/HessenbergMethod.h"

Matrix DoubleStepQRIteration(const Matrix &matrix);

Matrix DoubleStepQRIteration(Matrix &matrix, Matrix &P);

#endif //NUMERICAL_ALGEBRA_DOUBLESTEPQRITERATION_H
