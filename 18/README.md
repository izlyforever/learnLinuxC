## x86汇编程序基础

> 由于之前读过王爽《汇编语言》，所以只需要[对比一下](http://pld.cs.luc.edu/courses/264/now/notes/x64sheet.html)，基本也能懂一点 x86_64 汇编

汇编程序中以.开头的名称并不是指令的助记符，不会被翻译成机器指令，而是给汇编器一些特殊指示，称为汇编指示（Assembler Directive）或伪操作（Pseudo-operation），由于它不是真正的指令所以加个“伪”字。.section指示把代码划分成若干个段（Section），程序被操作系统加载执行时，每个段被加载到不同的地址，操作系统对不同的页面设置不同的读、写、执行权限。

> 参考简单实例： `hello.s`

.data段保存程序的数据，是可读可写的，相当于C程序的全局变量。

本程序中没有定义数据，所以.data段是空的。

.text段保存代码，是只读和可执行的，后面那些指令都属于.text段。

_start是一个符号（Symbol），符号在汇编程序中代表一个地址，可以用在指令中，汇编程序经过汇编器的处理之后，所有的符号都被替换成它所代表的地址值。在C语言中我们通过变量名访问一个变量，其实就是读写某个地址的内存单元，我们通过函数名调用一个函数，其实就是跳转到该函数第一条指令所在的地址，所以变量名和函数名都是符号，本质上是代表内存地址的。

int指令称为软中断指令，可以用这条指令故意产生一个异常（这个异常可以被 hook），上一章讲过，异常的处理和中断类似，CPU从用户模式切换到特权模式，然后跳转到内核代码中执行异常处理程序。

int指令中的立即数0x80是一个参数（对应8086 的 int 4c00h），在异常处理程序中要根据这个参数决定如何处理，在Linux内核中int $0x80这种异常称为系统调用（System Call）。内核提供了很多系统服务供用户程序使用，但这些系统服务不能像库函数（比如printf）那样调用，因为在执行用户程序时CPU处于用户模式，不能直接调用内核函数，所以需要通过系统调用切换CPU模式，经由异常处理程序进入内核，用户程序只能通过寄存器传几个参数，之后就要按内核设计好的代码路线走，而不能由用户程序随心所欲，想调哪个内核函数就调哪个内核函数，这样可以保证系统服务被安全地调用。在调用结束之后，CPU再切换回用户模式，继续执行int $0x80的下一条指令，在用户程序看来就像函数调用和返回一样。

eax和ebx的值是传递给系统调用的两个参数。eax的值是系统调用号，Linux的各种系统调用都是由int $0x80指令引发的，内核需要通过eax判断用户要调哪个系统调用，_exit的系统调用号是1。ebx的值是传给_exit的参数，表示退出状态。大多数系统调用完成之后会返回用户空间继续执行后面的指令，而_exit系统调用比较特殊，它会终止掉当前进程，而不是返回用户空间继续执行。

以上这些跟 DOS 上 8086 汇编十分相似

### 两种汇编写法

x86汇编的两种语法：intel语法和AT&T语法
x86汇编一直存在两种不同的语法，在intel的官方文档中使用intel语法，Windows也使用intel语法，而UNIX平台的汇编器一直使用AT&T语法，所以本书使用AT&T语法。movl %edx,%eax这条指令如果用intel语法来写，就是mov eax,edx，寄存器名不加%号，源操作数和目标操作数的位置互换，字长也不是用指令的后缀l表示而是用另外的方式表示。介绍x86汇编的书很多，UNIX平台的书都采用AT&T语法，其它书一般采用intel语法。

> 可参考: <https://www.cnblogs.com/idorax/p/6430884.html>

### 汇编寻址

汇编寻址方式可真丰富，并且可以和 C 语言的一些语法对标（ struct + 数组）

ADDRESS_OR_OFFSET(%BASE_OR_OFFSET,%INDEX,MULTIPLIER)

它所表示的地址可以这样计算出来：

FINAL ADDRESS = ADDRESS_OR_OFFSET + BASE_OR_OFFSET + MULTIPLIER * INDEX

### ELF

ELF文件格式是一个开放标准，各种UNIX系统的可执行文件都采用ELF格式，它有三种不同的类型：

可重定位的目标文件（Relocatable，或者Object File）

可执行文件（Executable）

共享库（Shared Object，或者Shared Library）

ELF格式提供了两种不同的视角，链接器把ELF文件看成是Section的集合，而加载器把ELF文件看成是Segment的集合。

目标文件需要链接器做进一步处理，所以一定有Section Header Table；可执行文件需要加载运行，所以一定有Program Header Table；而共享库既要加载运行，又要在加载时做动态链接，所以既有Section Header Table又有Program Header Table。

> readelf 可以查看具体的 elf 文件信息，详细的解释见图: ![elf](ELF_Executable_and_Linkable_Format_diagram_by_Ange_Albertini.png)

- `readelf -a max.o` 可以查看整个 `max.o` 的描述信息
- `hexdump -C max.o` 可以 `max.o` 当作文本打印出来 (关注一下中间打星的行)
- `objdump -d max.o` 可以查看反汇编

注意上述操作对 `max.o` 和 `max.out` 的异同点，另外二进制的大小也要关注
