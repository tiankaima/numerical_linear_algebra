# Mapping

此文档记录了教材《数值线性代数（第 2 版） 徐树方、高立、张平文》中算法与代码的对应关系。

## 1. 线性方程组的直接解法

### 1.1 三角形方程组和三角分解

#### 1.1.1 解下三角形方程组：前代法

[LowerTriangleMatrix_Solve_InPlace](./CustomMath_lib/GaussMethod/TriangleMatrix.cpp)

#### 1.1.2 解上三角形方程组：回代法

[UpperTriangleMatrix_Solve_InPlace](./CustomMath_lib/GaussMethod/TriangleMatrix.cpp)

#### 1.1.3 计算三角分解：Gauss 消去法

[LU_Decomposition_InPlace](./CustomMath_lib/GaussMethod/LU_Decomposition.cpp)

### 1.2 选主元三角分解

#### 1.2.1 计算全主元三角分解：全主元 Gauss 消去法

[LU_FP_Decomposition_InPlace](./CustomMath_lib/GaussMethod/LU_FP_Decomposition.cpp)

#### 1.2.2 计算列主元三角分解：列主元 Gauss 消去法

[LU_PP_Decomposition_InPlace](./CustomMath_lib/GaussMethod/LU_PP_Decomposition.cpp)

### 1.3 平方根法

#### 1.3.1 计算 Cholesky 分解：平方根法

[Cholesky_Decomposition_InPlace](./CustomMath_lib/CholeskyMethod/Cholesky_Decomposition.cpp)

#### 1.3.2 计算 $LDL^T$ 分解：改进的平方根法

[Cholesky_LDLT_Decomposition_InPlace](./CustomMath_lib/CholeskyMethod/Cholesky_Decomposition.cpp)

## 2. 线性方程组的敏度分析与消去法的舍入误差分析

### 2.5 计算解的精度估计和迭代改进

#### 2.5.1 估计矩阵的 $1$ 范数：优化法

- 矩阵的 $1$ 范数估计：[MatrixNorm_1](./CustomMath_lib/InfinityNorm/InfinityNorm.h)
- 矩阵 $A$ 对应的 $A^{-T}$ 的 $1$ 范数估计：[MatrixNorm_A_Inv_T_1](./CustomMath_lib/InfinityNorm/InfinityNorm.h)

## 3. 最小二乘问题的解法

### 3.2 初等正交变换

#### 3.2.1 计算 Householder 变换

[HouseHolderMethod](./CustomMath_lib/HouseholderMethod/HouseholderMethod.cpp)

### 3.3 正交变换法

#### 3.3.1 计算 QR 分解：Householder 方法

[QR_Decomposition](./CustomMath_lib/HouseholderMethod/HouseholderMethod.cpp)

## 4. 线性方程组的古典迭代法

### 4.1 单步线性定常迭代法

#### 4.1.1 Jacobi 迭代法

[JacobiIteration](./CustomMath_lib/IterationMethod/IterationMethod.cpp)

#### 4.1.2 Gauss-Seidel 迭代法

[GaussSeidelIteration](./CustomMath_lib/IterationMethod/IterationMethod.cpp)

### 4.4 超松弛迭代法

[SORIteration](./CustomMath_lib/IterationMethod/IterationMethod.cpp)

## 5. 共轭梯度法

### 5.3 实用共轭梯度法及其收敛性

#### 5.3.1 解对称正定线性方程组：实用共轭梯度法

[ConjugateGradientMethod](./CustomMath_lib/IterationMethod/IterationMethod.cpp)

## 6. 非对称特征值问题的计算方法

### 6.2 幂法

- 幂法求最大特征值：[PowerIteration](./CustomMath_lib/PowerIteration/PowerIteration.cpp)
- 幂法求多项式最大根: [MaxRootForPolynomial](./CustomMath_lib/PowerIteration/PowerIteration.cpp)

### 6.4 QR 方法

#### 6.4.1 计算上 Hessenberg 分解：Householder 变换

[HessenbergMethod](./CustomMath_lib/HessenbergMethod/HessenbergMethod.cpp)

#### 6.4.2 双重步位移的 QR 迭代

[DoubleShiftQRMethod](./CustomMath_lib/QRMethod/DoubleShiftQRMethod.cpp)

