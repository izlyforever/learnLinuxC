## goto语句和标号

goto语句过于强大了，从程序中的任何地方都可以无条件跳转到任何其它地方，只要在那个地方定义一个标号就行，唯一的限制是goto只能跳转到同一个函数中的某个标号处，而不能跳到别的函数中。

滥用goto语句会使程序的控制流程非常复杂，可读性很差。著名的计算机科学家Edsger W. Dijkstra最早指出编程语言中goto语句的危害，goto语句不是必须存在的，提倡取消goto语句。

C标准库函数setjmp和longjmp配合起来可以实现函数间的跳转，但只能从被调用的函数跳回到它的直接或间接调用者（同时从栈空间弹出一个或多个栈帧），而不能从一个函数跳转到另一个和它毫不相干的函数中。setjmp/longjmp函数主要也是用于出错处理，比如函数A调用函数B，函数B调用函数C，如果在C中出现某个错误条件，使得函数B和C继续执行下去都没有意义了，可以利用setjmp/longjmp机制快速返回到函数A做出错处理 [APUE2e] Advanced Programming in the UNIX Environment. 2. W. Richard Stevens和Stephen A. Rago.

wocao，switch 是特殊的 goto，可以用来做循环展开（见 `gotoExample.c`）太优雅了吧！
