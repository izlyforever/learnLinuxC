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

## main 函数和启动

gcc main.o -o main其实是调用ld做链接的，相当于这样的命令：

``` shell
ld /usr/lib/crt1.o /usr/lib/crti.o main.o -o main -lc -dynamic-linker /lib/ld-linux.so.2
```

lc选项是gcc默认的，不用写，而对于ld则不是默认选项，所以要写上。-dynamic-linker /lib/ld-linux.so.2指定动态链接器是/lib/ld-linux.so.2，

`_start` 调用 `__libc_start_main` 再调用 `main`。则它调用main函数的形式是： `exit(main(argc, argv));`

exit也是libc中的函数，它首先做一些清理工作，然后调用上一章讲过的_exit系统调用终止进程，main函数的返回值最终被传给_exit系统调用，成为进程的退出状态。我们也可以在main函数中直接调用exit函数终止进程而不返回到启动例程

按照惯例，退出状态为0表示程序执行成功，退出状态非0表示出错。注意，退出状态只有8位，而且被Shell解释成无符号数，如果将上面的代码改为exit(-1);或return -1;，则运行结果为 255

## 内联汇编

内联汇编在 webrtc 中还是挺常见的，但是要写好几个版本才能做到真的跨平台。

## volatile限定符

> volatile限定符 确保了不会乱序，每条语句都会执行，不会被优化，对于特殊内存十分有必要

如果串口发送寄存器的地址被Cahce缓存，CPU执行单元对串口发送寄存器做写操作都写到Cache中去了，串口发送寄存器并没有及时得到数据，也就不能及时发送，CPU执行单元先后发出的1、2、3三个字节都会写到Cache中的同一个单元，最后Cache中只保存了第3个字节，如果这时Cache把数据写回到串口发送寄存器，只能把第3个字节发送出去，前两个字节就丢失了。与此类似，如果串口接收寄存器的地址被Cache缓存，CPU执行单元在读第1个字节时，Cache会从串口接收寄存器读上来缓存，然而串口接收寄存器后面收到的2、3两个字节Cache并不知道，因为Cache把串口接收寄存器当作普通内存单元，并且相信内存单元中的数据是不会自己变的，以后每次读串口接收寄存器时，Cache都会把缓存的第1个字节提供给CPU执行单元。

通常，有Cache的平台都有办法对某一段地址范围禁用Cache，一般是在页表中设置的，可以设定哪些页面允许Cache缓存，哪些页面不允许Cache缓存，MMU不仅要做地址转换和访问权限检查，也要和Cache协同工作。

除了设备寄存器需要用volatile限定之外，当一个全局变量被同一进程中的多个控制流程访问时也要用volatile限定，比如信号处理函数和多线程。