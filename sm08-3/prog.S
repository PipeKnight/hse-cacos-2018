﻿	.text
	.global main
main:
	call	readi32
	movl	%eax, %ebx
	jmp	cycle
	call	finish

cycle:
	cmpl	$0, %ebx
	jl	exit
	movl	%ebx, %eax
	call	writei32
	call	nl
	decl	%ebx
	jmp	cycle

exit:
	call	finish
