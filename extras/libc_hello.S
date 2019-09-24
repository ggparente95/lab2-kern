.global main
main:
        push $msg
        call strlen
        mov %eax,len(,1)
        push $msg
        push $1

        call write

        push $7
        call _exit

.data
msg:
        .ascii "Hello, world!\n"
len:
        .byte 0