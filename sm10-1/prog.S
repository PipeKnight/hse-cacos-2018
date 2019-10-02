//	.data
//A:	.quad	1231231123
//B:	.quad	124112123
        .text
	.global process
_form:
        .asciz  "%llu\n"
        .global process
	.global main
process:
        push    %ebp
        movl    %esp, %ebp
	
	subl    $16, %esp 
        movq    A, %xmm0
        movq    B, %xmm1
        psllq   $1, %xmm0
        psrlq   $1, %xmm1
        psubq   %xmm1, %xmm0
        movq    %xmm0, (%esp)
        push    $_form
        call    printf
	
        movl    %ebp, %esp
        popl    %ebp
        ret

//main:
//	call process
//	call finish
