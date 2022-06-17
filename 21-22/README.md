## 预处理

`echo | gcc -E -dM -` 可以看到当前 gcc 预定义的宏

`gcc -i main.cpp` 生成 `main.i` 的过程会去掉所有的注释，把宏展开，带上函数的位置，但是**不进行语法检测**

除非平台相关、编译器的宏、变长参数的宏、和 c 中一些函数不用宏很难写（或者写的很不优雅）之外，尽量不要用宏

> C++ 中有 constexpr 和 模板，导致宏没有那么泛滥，但是 C 里面宏非常普通

总之适度使用宏（并不一定效率更快），另外有 side effect 的时候更要小心

`__func__`, `__line__`, `#`, `##`, assert, 然后还有一些指令集相关、平台相关、编译器相关和一些 feature 相关的宏，都是重要不可获取的宏

关于数组和字符串很经典的宏

``` cpp
// strlen() for string constant
#define STRLEN(CONST_STR) (sizeof(CONST_STR) - 1)

// calculate the length of an array
#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))
```

> 注意 sizeof 不是函数，这些都是编译器完成的东西，这里 ARRLEN(arr) 转成 int 可能不是特别合理，但其实一般情况肯定够了


## Makefile

看上去现在没必要学习复杂的 makefile 规则，只要会写 cmake 或者 xmake 即可，但是也不妨碍大致了解一下（或者从别人项目照搬然后修改）

