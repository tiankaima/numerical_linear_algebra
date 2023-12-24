//
// Created by TianKai Ma on 2023/12/19.
//

#ifndef NUMERICAL_ALGEBRA_SVDMETHOD_H
#define NUMERICAL_ALGEBRA_SVDMETHOD_H

#include "../../includes/NLAMethods.h"

typedef struct {
    Matrix U;
    Matrix S;
    Matrix V;
} SVDMethod_Result;

#endif //NUMERICAL_ALGEBRA_SVDMETHOD_H
