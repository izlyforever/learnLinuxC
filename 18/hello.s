.section .text
.global _start
_start:
  movl $1, %eax
  movl $4, %ebx

  int $0x80

# echo $? output 4
# 1 stand for _exit in system call
# 4 is the return value
