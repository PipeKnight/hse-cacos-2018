        .text
        .global process
process:
        push    %ebp
        movl    %esp, %ebp
	andl	$-16, %esp
        push    %ebx
        push    %esi
	push	%edi
	
        movl    8(%ebp), %ecx	// pointer to p
	movl	12(%ebp), %edi	// int i
        movl    (%ecx), %eax	// U
        mull	8(%ecx,%edi,4)	// *W[i]
        movl    %eax, %ebx	// U * W[i] (eax)
        movl    %edx, %esi	// U * W[i] (edx)
        movl    4(%ecx), %eax	// V
        imull	24(%ecx)	// *X
        addl    %ebx, %eax
	adcl	$0, %edx
        addl    %esi, %edx
        jno     exit
        movl    $-1, %eax
        movl    $-1, %edx
exit:
	popl	%edi
        popl    %esi
        popl    %ebx
        movl    %ebp, %esp
        popl    %ebp
        ret