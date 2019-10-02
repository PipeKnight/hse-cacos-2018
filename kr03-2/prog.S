        .text
        .global process

process:
        push    %ebp
        movl    %esp, %ebp

	movsbl	12(%esp), %eax
	
	imull   $4, %eax
	jo      overflow
	movl	%eax, %ecx

        movl	16(%esp), %eax
	
        imull   $5, %eax
        jo      overflow
        subl    %ecx, %eax
        jo      overflow

normal:
	//call	writei32
        movl    8(%esp), %ecx
        movl    %eax, (%ecx)
        xorl    %eax, %eax
	movl    %ebp, %esp
        popl    %ebp
        ret

overflow:
	//call	writei32
	movl    $1, %eax
	movl    %ebp, %esp
        popl    %ebp
        ret
        