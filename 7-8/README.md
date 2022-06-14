组合使得系统可以任意复杂，而抽象使得系统的复杂性是可以控制的，任何改动都只局限在某一层，而不会波及整个系统。

Butler Lampson: All problems in computer science can be solve by another level of indirection

计算机的所有问题都可以听过添加一层来解决，除了层过多的事情

## 数组

C99的新特性允许在数组长度表达式中使用变量，称为变长数组（VLA，Variable Length Array），VLA只能定义为局部变量而不能是全局变量，与VLA有关的语法规则比较复杂，而且很多编译器不支持这种新特性，不建议使用（C++ 都不用）。

> 递归 + struct + 数组 真是 C 语言的光辉

一堆数组访问负数下标是被允许的，这样做可以支持很多骚操作

多维数组的概念模型是多维的，物理模型一维，但这不印象看上去像多维的，见代码：`arrayLen.c`

