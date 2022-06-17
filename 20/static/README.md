# 实验

- `gcc -c stack/stack.c stack/push.c stack/pop.c stack/is_empty.c`
- `ar rs libstack.a stack.o push.o pop.o is_empty.o`
- `objdump -d main`

不同于 `gcc main.c stack.o push.o pop.o is_empty.o -Istack`，这就是静态链接的好处
