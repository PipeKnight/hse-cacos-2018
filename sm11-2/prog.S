        .text
        .global _start
_start:
        subl    $4, %esp
	jmp	read
replace:
	subl	$32, %eax
	movl    %eax, (%esp)
	jmp	write
read:
        movl    $3, %eax
        movl    $0, %ebx
	movl    $1, %edx
        leal    (%esp), %ecx
        int     $0x80

        testl	%eax, %eax
	jz	exit
        movzbl  (%esp), %eax
	cmpl    $'z', %eax
        jg      write
        cmpl    $'a', %eax
        jl      write
        jmp	replace
write:
        movl    $4, %eax
        movl    $1, %ebx
        leal    (%esp), %ecx
        movl    $1, %edx
        int     $0x80
        jmp     read
exit:
        movl    $1, %eax
        xorl    %ebx, %ebx
	xorl    %ecx, %ecx
	xorl    %edx, %edx
        int     $0x80
