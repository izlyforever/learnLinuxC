## C标准库

总结一下，Linux平台提供的C标准库包括：

一组头文件，定义了很多类型和宏，声明了很多库函数。这些头文件放在哪些目录下取决于不同的编译器，在我的系统上，stdarg.h和stddef.h位于/usr/lib/llvm-7/lib/clang/7.1.0/include/目录下，stdio.h、stdlib.h、time.h、math.h、assert.h位于/usr/include目录下。C99标准定义的头文件有24个，本书只介绍其中最基本、最常用的几个。

一组库文件，提供了库函数的实现。大多数库函数在libc共享库中，有些库函数在另外的共享库中，例如数学函数在libm中。通常libc共享库是/lib/libc.so.6，而我的系统启用了hwcap机制，libc共享库是/lib//lib/x86_64-linux-gnu/libc.so.6。

> 总之多查查 man 没坏处

C99的restrict关键字

C99引入restrict关键字，如果程序员把上面的函数声明为void vector_add(const double *restrict x, const double *restrict y, double *restrict result)，就是告诉编译器可以放心地对这个函数做优化，程序员自己会保证这些指针所指的内存区间互不重叠。

### 字符串函数

> 以下不全是 C 标准函数，有些是 Posix标准（多查查 man），多注意线程安全

``` cpp
char *strdup(const char *s);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);
char *strchr(const char *s, int c);
char *strrchr(const char *s, int c);
char *strtok(char *str, const char *delim);
char *strtok_r(char *str, const char *delim, char **saveptr);
```

### 文件的基本概念

fopen/fclose/stdin/stdout/stderr

errno与perror函数

很多系统函数在错误返回时将错误原因记录在libc定义的全局变量errno中，每种错误原因对应一个错误码，请查阅errno(3)的Man Page了解各种错误码，errno在头文件errno.h中声明，是一个整型变量，所有错误码都是正整数。

fputc函数向指定的文件写一个字节，putchar向标准输出写一个字节，调用putchar(c)相当于调用fputc(c, stdout)。

### 格式化I/O函数

``` cpp
#include <stdio.h>

int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);

#include <stdarg.h>

int vprintf(const char *format, va_list ap);
int vfprintf(FILE *stream, const char *format, va_list ap);
int vsprintf(char *str, const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);
```


### C标准库的I/O缓冲区

用户程序调用C标准I/O库函数读写文件或设备，而这些库函数要通过系统调用把读写请求传给内核（以后我们会看到与I/O相关的系统调用），最终由内核驱动磁盘或设备完成I/O操作。C标准库为每个打开的文件分配一个I/O缓冲区以加速读写操作，通过文件的FILE结构体可以找到这个缓冲区，用户调用读写函数大多数时候都在I/O缓冲区中读写，只有少数时候需要把读写请求传给内核。

> 其实在调_exit进内核之前还要调用户程序中通过atexit(3)注册的退出处理函数

### 内存分配函数

``` cpp
#include <stdlib.h>
void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
```

> calloc的参数很像fread/fwrite的参数，分配nmemb个元素的内存空间，每个元素占size字节，并且calloc负责把这块内存空间用字节0填充，而malloc并不负责把分配的内存空间清零。

### 编码方式

[Unicode和UTF-8](https://akaedu.github.io/book/apas02.html)

[Linux 编程中使用 UTF-8](https://akaedu.github.io/book/apas03.html)

常用汉字也都位于BMP中，所以一个汉字的存储通常占3个字节。例如编辑一个C程序 `nihao.c`，可以 `od -tc nihao.c` 查看计算机中存储的内容

### 总结

<https://akaedu.github.io/book/ch27.html>
