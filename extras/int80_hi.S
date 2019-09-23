#include <sys/syscall.h>  // SYS_write, SYS_exit

.globl main
main:
        mov $SYS_write, %eax   // %eax == syscall number
        mov $1, %ebx           // %ebx == 1st argument (fd)
        mov $msg, %ecx         // %ecx == 2nd argument (buf)
        mov $len, %edx         // %edx == 3rd argument (count)
        int $0x80

        mov $SYS_exit, %eax
        mov $7, %ebx
        int $0x80

.data
msg:
        .ascii "Hello, world!\n"

.set len, . - msg