        .data
A:	.int	1
B:	.int	2
C:	.int	3
//X:	.int	5
        .text
        .global process
	.global A
	.global B
	.global C
	//.global X
	//.global main

process:
        movl	B, %eax
	mull	X
	mull	X
	movl	$0, %ecx
	subl	%eax, %ecx
	subl    %eax, %ecx
        movl    A, %eax
        mull	X
        mull	X
        mull	X
	addl	%eax, %ecx
	addl    C, %ecx
	movl	%ecx, %eax
		
        //movl    %ebp, %esp
        //popl    %ebp
        ret

//main:
//	call process
//	call writei32
//	call finish
