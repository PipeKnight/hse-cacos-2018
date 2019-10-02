        .text
        .global forward.args
forward.args:
        push    %ebp
        movl    %esp, %ebp
	andl	$-16, %esp

	pushl	$0
	pushl	8(%ebp)
	pushl	$0
        pushl	16(%ebp)
	movl	20(%ebp), %ecx
        calll   process
        xorl    %edx, %edx
	
        movl    %ebp, %esp
        popl    %ebp
        ret