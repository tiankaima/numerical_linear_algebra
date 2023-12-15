# Mapping

此文档记录了教材《数值线性代数（第2版） 徐树方、高立、张平文》中算法与代码的对应关系。

## 1. 线性方程组的直接解法

### 1.1 三角形方程组和三角分解

#### 1.1.1 解下三角形方程组：前代法

[LowerTriangleMatrix_Solve_InPlace](./CustomMath_lib/GaussMethod/TriangleMatrix.cpp)

#### 1.1.2 解上三角形方程组：回代法

[UpperTriangleMatrix_Solve_InPlace](./CustomMath_lib/GaussMethod/TriangleMatrix.cpp)

#### 1.1.3 计算三角分解：Gauss消去法

[LU_Decomposition_InPlace](./CustomMath_lib/GaussMethod/LU_Decomposition.cpp)

### 1.2 选主元三角分解

#### 1.2.1 计算全主元三角分解：全主元Gauss消去法

[LU_FP_Decomposition_InPlace](./CustomMath_lib/GaussMethod/LU_FP_Decomposition.cpp)

#### 1.2.2 计算列主元三角分解：列主元Gauss消去法

[LU_PP_Decomposition_InPlace](./CustomMath_lib/GaussMethod/LU_PP_Decomposition.cpp)