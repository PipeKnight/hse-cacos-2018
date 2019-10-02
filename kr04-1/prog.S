        .text
        .global forward.args
forward.args:
        push    %ebp
        movl    %esp, %ebp
	andl	$-16, %esp
	
	movl	12(%ebp), %edx
        movl    16(%ebp), %eax
	cdq
        pushl	8(%ebp)
	pushl	%edx
        pushl	%eax
        pushl	20(%ebp)
        calll	process
	movl	%eax, %edx
        movl	$0, %eax
	subl	%edx, %eax
	xorl	%edx, %edx

        movl    %ebp, %esp
        popl    %ebp
        ret
