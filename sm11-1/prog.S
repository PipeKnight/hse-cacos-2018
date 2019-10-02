#define __NR_exit 1
#define __NR_read 3
#define __NR_write 4
#define __NR_brk 45
        .text
        .global _start
_start:
        subl    $4, %esp
read:
        movl    $__NR_read, %eax
        movl    $0, %ebx
	movl    $1, %edx
        leal    (%esp), %ecx
        int     $0x80

        testl	%eax, %eax
	jz	exit
        movzbl  (%esp), %eax
	addl    $-48, %eax
        cmpl    $10, %eax
	jnb	write
        movl    $'0', %eax
        movl    %eax, (%esp)
write:
        movl    $__NR_write, %eax
        movl    $1, %ebx
        leal    (%esp), %ecx
        movl    $1, %edx
        int     $0x80
        jmp     read
exit:
        movl    $__NR_exit, %eax
        xorl    %ebx, %ebx
	xorl    %ecx, %ecx
	xorl    %edx, %edx
        int     $0x80
