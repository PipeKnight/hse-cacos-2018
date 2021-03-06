﻿	.text
	.global main
main:
	movl	$0, %esi
	movl	$0, %edi
	jmp	read

read:	
	call	readi32
	jc	exit
	testl	$1, %eax
	jz	even
	jnz	odd

zero:
	cmpl	$0, %eax
	jl	odd
	jge	even

one:
	cmpl	$0, %eax
	jl	even
	jge	odd

odd:
	addl	%eax, %esi
	jmp	read

even:
	addl	%eax, %edi
	jmp	read

exit:
	movl	%edi, %eax
	call	writei32
	call	nl
	movl	%esi, %eax
	call	writei32
	call	nl
	call	finish