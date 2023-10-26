#set text(
    font: "Source Han Serif SC",
    size: 10pt,
)
#set math.equation(numbering: "(1)")

#align(center, text(20pt)[
    数值代数实验报告 2
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
- 点击”本地Windows调试器“的右侧三角形按钮运行
]

#pagebreak()

= 问题描述
== 2.1

估计 $5$ 到 $20$ 阶 Hilbert 矩阵的 $infinity$ 范数条件数

== 2.2

设
$
A_n = mat(delim:"[",
    1, 0, 0, 0, dots.c, 1;
    -1, 1, 0, 0, dots.c, 1;
    -, -1, 1, 0, dots.c, 1;
    dots.v, dots.v, dots.v, dots.v, dots.down, dots.v;
    -1, dots.c, -1, -1, 1, 1;
    -1, dots.c, -1, -1, -1, 1;
) in RR^(n x n)
$
随机选取 $x in RR^n$，并计算出 $b = A_n x$, 然后用列主元高斯消去法求解该方程组。用 p69 页公式估计 $n$ 从 $5$ 到 $30$ 时计算解 $hat(x)$ 的精度，并与真实相对误差作比较。要求输出真实相对误差和估计的相对误差上界。

#pagebreak()

= 程序介绍

- 复用了上次作业的全部代码。重构了部分逻辑使所有代码使用`unsigned long` 以及`long double`类型，确保精度问题。
- 修改了上次提交时选主元消去结果误差巨大的问题（单独考虑对角线全1的情况）
- 矩阵的1-范数估计的实现方法在`CustomMath_lib/InfinityNorm/InfinityNorm.cpp`中，分别提供了两种办法计算$norm(A)_1$ 和$norm(A^(-T))_1$
- 本次作业提交在`homeworks/homework_2.cpp`中

#pagebreak()

= 运行结果

```txt
------ Q 2.1 ------
n = 5, condition_number = 943656.0000000018689
n = 6, condition_number = 29070279.00000236591
n = 7, condition_number = 985194886.5019417926
n = 8, condition_number = 33872791096.51495649
n = 9, condition_number = 1099654542182.044117
n = 10, condition_number = 35357438794311.81662
n = 11, condition_number = 1233700677314114.901
n = 12, condition_number = 41152583629496310.3
n = 13, condition_number = 1323308355530996361
n = 14, condition_number = 4.514480476929424986e+19
n = 15, condition_number = 2.372051355568131468e+21
n = 16, condition_number = 2.476114807729196188e+21
n = 17, condition_number = 2.128317989845009304e+21
n = 18, condition_number = 3.706607164001239419e+21
n = 19, condition_number = 2.656854800573346314e+21
n = 20, condition_number = 4.307025616349245435e+22
------ Q 2.2 ------
n = 5
real diff = 0
calculated diff = 0
diff in diff = 0
n = 6
real diff = 0
calculated diff = 0
diff in diff = 0
n = 7
real diff = 0
calculated diff = 0
diff in diff = 0
n = 8
real diff = 0
calculated diff = 0
diff in diff = 0
n = 9
real diff = 0
calculated diff = 0
diff in diff = 0
n = 10
real diff = 0
calculated diff = 0
diff in diff = 0
n = 11
real diff = 0
calculated diff = 0
diff in diff = 0
n = 12
real diff = 1.734723475976807094e-18
calculated diff = 6.612014234494321208e-18
diff in diff = 4.877290758517514114e-18
n = 13
real diff = 2.775557561562891351e-17
calculated diff = 1.010805595288567532e-16
diff in diff = 7.332498391322783968e-17
n = 14
real diff = 0
calculated diff = 0
diff in diff = 0
n = 15
real diff = 2.860979249076398383e-16
calculated diff = 7.249472996104535398e-16
diff in diff = 4.388493747028137015e-16
n = 16
real diff = 5.559768866249354567e-16
calculated diff = 1.567047177758013681e-15
diff in diff = 1.011070291133078224e-15
n = 17
real diff = 1.004799640629047946e-15
calculated diff = 3.496455435560005585e-15
diff in diff = 2.491655794930957639e-15
n = 18
real diff = 6.14552570651475634e-16
calculated diff = 2.351142373483552314e-15
diff in diff = 1.73658980283207668e-15
n = 19
real diff = 2.217842437587711137e-15
calculated diff = 9.386353512628392564e-15
diff in diff = 7.168511075040681427e-15
n = 20
real diff = 3.291862266251029277e-15
calculated diff = 1.90430239171948247e-14
diff in diff = 1.575116165094379542e-14
n = 21
real diff = 5.239604687546524397e-15
calculated diff = 1.492253799195121321e-14
diff in diff = 9.682933304404688812e-15
n = 22
real diff = 2.762792910639579795e-14
calculated diff = 1.056866738955917202e-13
diff in diff = 7.805874478919592225e-14
n = 23
real diff = 2.01765896295918722e-14
calculated diff = 8.778261422489434963e-14
diff in diff = 6.760602459530247742e-14
n = 24
real diff = 8.520916509357622023e-15
calculated diff = 2.945177052358312678e-14
diff in diff = 2.093085401422550476e-14
n = 25
real diff = 1.933140316207661783e-13
calculated diff = 7.61381409311802854e-13
diff in diff = 5.680673776910366756e-13
n = 26
real diff = 5.375343117701421744e-13
calculated diff = 1.327550673943842739e-12
diff in diff = 7.900163621737005642e-13
n = 27
real diff = 6.018842530046321184e-14
calculated diff = 1.970167956926096132e-13
diff in diff = 1.368283703921464014e-13
n = 28
real diff = 4.199517687703756253e-13
calculated diff = 1.313682704452139813e-12
diff in diff = 8.937309356817641882e-13
n = 29
real diff = 3.691738107736230547e-12
calculated diff = 1.133693937670085629e-11
diff in diff = 7.645201268964625745e-12
n = 30
real diff = 4.616569611648569034e-13
calculated diff = 1.056317222467293025e-12
diff in diff = 5.946602613024361212e-13
```

#pagebreak()

= 结果分析

方便分析数据，使用python绘制了两份图表：

== Hilbert 矩阵的条件范数

#image("img/2/hilbert_condition_number.png")

== 估计的相对误差 / 真实误差

#image("img/2/error_inspection.png", width: 85%)
