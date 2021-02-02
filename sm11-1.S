#include <asm/unistd_32.h>
        .data
c:
        .byte   0
        .text
        .global _start
_start:
        movl    $__NR_read, %eax
        movl    $0, %ebx
        movl    $c, %ecx
        movl    $1, %edx
        int     $0x80

        testl   %eax, %eax
        jz      exit

        movl    $'0', %esi
        movl    $'9', %edi

        cmpl    %esi, c
        jl      print
        cmpl    c, %edi
        jl      print

        movl    %esi, c
print:
        movl    $__NR_write, %eax
        movl    $1, %ebx
        movl    $c, %ecx
        movl    $1, %edx
        int     $0x80
        jmp     _start
exit:
        movl    $__NR_write, %eax
        movl    $1, %ebx
        movl    $'\n', %ecx
        movl    $1, %edx
        int     $0x80

        movl    $__NR_exit, %eax
        xorl    %ebx, %ebx
        int     $0x80
