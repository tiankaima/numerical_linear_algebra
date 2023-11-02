#set text(
    font: "Source Han Serif SC",
    size: 10pt,
)
#set math.equation(numbering: "(1)")

#align(center, text(20pt)[
    数值代数实验报告 3
])
#align(center, text(12pt)[
    PB21000030 马天开
])
#align(center, text(12pt)[
    #datetime.today().display("[year] 年 [month] 月 [day] 日")
])
#v(2cm)

#box(
fill: yellow.lighten(90%),
width: 100%,
inset: 12pt,
outset: 0pt,
radius: 0pt,
clip: true,
)[

=== GitHub仓库
```txt
https://github.com/tiankaima/numerical_algebra
```

=== 目录结构
- `CustomMath_lib`存放了具体的算法实现
- `Doctest_tests`存放了单元测试
- `homeworks`存放了作业的源代码，并且在`main.cpp`对每次作业进行了调用
- `Mathematica`存放了`.nb`文件，用于生成测试数据
- `writeups`存放了实验报告的源代码，比如本文

=== Linux 平台编译
```txt
> mkdir build
> cd build
> cmake ..
> make
```

=== 运行
```txt
./numerical_algebra
```

=== Windows 平台编译 & 运行
- 使用 Visual Studio 打开`numerical_algebra.sln`
- 在“解决方案资源管理器”中右键`numerical_algebra`，选择“设为启动项目”
- 点击“本地Windows调试器”的右侧三角形按钮运行
]

#pagebreak()

= 问题描述
将 QR 分解算法编写成通用的子程序, 并编写求解线性方程组和线性最小二乘问题的子程序，然后用你编写的程序完成以下计算任务:

== 3.1
求解第一章上级习题的三个方程组，并比较计算结果，并评述各方法的优劣。要求输出计算结果和准确解的误差以及运行时间。

== 3.2
求二次多项式 $y = a t^2 + b t + c$, 使得残向量在二范数最小的意义下拟合第二题数据。要求输出计算结果，残向量的二范数以及运行时间。

== 3.3

采用线性模型 $y = x_0 + a_1 x_1 + a_2 x_2 + · · · + a_(11)x_(11)$ 拟合第三题数据。求出模型中参数的最小二乘结果。要求输出计算结果，残向量的二范数以及运行时间。

#pagebreak()

= 程序介绍

- 复用了上次作业的全部代码，修正了一些错误。
- 用 macro 重写了下测试用的语句，现在看起来能简洁一些。
- 算法 3.2.1 算法 3.3.1 实现在`CustomMath_lib/HouseholderMethod/HouseholderMethod.cpp`中
- 本次作业提交在`homeworks/homework_3.cpp`中

= 运行结果

```txt
######  Q1_1  ######
LU_Solve_InPlace              diff = 3.6226e+08                    time = 4819     ms
LU_FP_Solve_InPlace           diff = 1.2896e-06                    time = 2783     ms
LU_PP_Solve_InPlace           diff = 1.2896e-06                    time = 1544     ms
Cholesky_Solve_InPlace        diff = 3.38341e+15                   time = 815      ms
Cholesky_LDLT_Solve_InPlace   diff = 6.46278                       time = 711      ms
QR_Solve_InPlace              diff = nan                           time = 19311    ms

######  Q1_2  ######
LU_Solve_InPlace              diff = 0                             time = 2140     ms
LU_FP_Solve_InPlace           diff = 5.87475e-16                   time = 4186     ms
LU_PP_Solve_InPlace           diff = 0                             time = 2485     ms
Cholesky_Solve_InPlace        diff = 2.16137e-15                   time = 1494     ms
Cholesky_LDLT_Solve_InPlace   diff = 1.57009e-16                   time = 1226     ms
QR_Solve_InPlace              diff = 1.4631e-14                    time = 30657    ms

######  Q1_3  ######
LU_Solve_InPlace              diff = 1.71733e-12                   time = 148      ms
LU_FP_Solve_InPlace           diff = 1.71381e-14                   time = 1360     ms
LU_PP_Solve_InPlace           diff = 4.55868e-15                   time = 341      ms
Cholesky_Solve_InPlace        diff = 7.37231e+08                   time = 134      ms
Cholesky_LDLT_Solve_InPlace   diff = 7.35431e-14                   time = 108      ms
QR_Solve_InPlace              diff = 2.07766e-13                   time = 2886     ms

######  Q2  ######
[1,1,1]

######  Q3  ######
[2.07752,0.718888,9.6802,0.153506,13.6796,1.98683,-0.958225,-0.484023,-0.0736469,1.0187,1.44352,2.90279]
```

= 结果分析

使用 Mathematica 校验了相关结果，位置在 `Mathematica/homework_1.nb`

#strike[但其实并没有想明白Q1_1用QR做不出来]