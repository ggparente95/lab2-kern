.global main
main:

        push $msg
        call puts

        pop %ecx

        mov $0,%eax
        ret

.data
msg:
        .ascii "Hello, world!\n"