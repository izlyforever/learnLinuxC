# 汇编与 C 的关系

对于一个简单正常的 `testFunCall.c`，我们可以使用 `gcc testFunCall.c`，然后 `gdb a.out` 然后 start
再 layout src 再 s 两次，再 bt 看看堆栈，看看函数参数。然后 `disassemble` 可以看到函数的反汇编

> 虽然是个很简单的函数，但是完整的走一遍，以便后面不常规的函数也能精准预测

- start 后 `info r` 可以看到寄存器的值是不确定的
- disassemble 可以看到先把 3 给了 esi 再把 2 给了 edi（反序的耶）
- 后面它要 push 参数（但是不是简单的 push 而是直接计算的方式 mov
- 然后就感觉是一块内存把函数名和参数都压入到栈中




注意函数调用和返回过程中的这些规则：

- 参数压栈传递，并且是从右向左依次压栈。
- ebp总是指向当前栈帧的栈底。
- 返回值通过eax寄存器传递。

这些规则并不是体系结构所强加的，ebp寄存器并不是必须这么用，函数的参数和返回值也不是必须这么传，只是操作系统和编译器选择了以这样的方式实现C代码中的函数调用，这称为Calling Convention，Calling Convention是操作系统二进制接口规范（ABI，Application Binary Interface）的一部分。

