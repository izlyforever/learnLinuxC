## 进程

我们知道，每个进程在内核中都有一个进程控制块（PCB）来维护进程相关的信息，Linux内核的进程控制块是task_struct结构体。现在我们全面了解一下其中都有哪些信息。

进程id。系统中每个进程有唯一的id，在C语言中用pid_t类型表示，其实就是一个非负整数。

进程的状态，有运行、挂起、停止、僵尸等状态。

进程切换时需要保存和恢复的一些CPU寄存器。

描述虚拟地址空间的信息。

描述控制终端的信息。

当前工作目录（Current Working Directory）。

umask掩码。

文件描述符表，包含很多指向file结构体的指针。

和信号相关的信息。

用户id和组id。

控制终端、Session和进程组。

进程可以使用的资源上限（Resource Limit）

子进程会 copy 父进程的信息，只有 getppid、getpid 等信息不一致，gdb 也不能进行多进程的 debug，只能
set follow-fork-mode child命令设置gdb在fork之后跟踪子进程（set follow-fork-mode parent则是跟踪父进程），然后用run命令，看到的现象是父进程一直在运行，在(gdb)提示符下打印消息，而子进程被先前设的断点打断了。

### 进程间通信（IPC，InterProcess Communication）

``` cpp
#include <unistd.h>

int pipe(int filedes[2]);
```

两个进程通过一个管道只能实现单向通信，比如 pipe.c 的例子，父进程写子进程读，如果有时候也需要子进程写父进程读，就必须另开一个管道。
