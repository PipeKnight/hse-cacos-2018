	.data
INTMAX:	.int	0x7FFFFFFF
SUM:	.int	0
ZERO:	.int	0
ONE:	.int	1
	.text
	.global main
main:
	movl	SUM, %edi
	call	readi32
	jc	exit
	cmpl	$0, %eax
	cmovs	ONE, %esi
	cmovns	ZERO, %esi
	addl	INTMAX, %esi
	addl	%eax, %edi
	cmovo	%esi, %edi
	movl	%edi, SUM
	jno	main
	
exit:	
	movl	%edi, %eax
	call 	writei32
	call	nl
	call 	finish
