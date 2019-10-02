        .text
        .global mul64p

form2:
        .asciz  "%llx%0*llx\n"
form1:
	.asciz	"%llx\n"

mul64p:
        pushl   %ebp
	movl    %esp, %ebp
	
        pushl   %ebx
        pushl   %edi
        pushl   %esi
	
	movl    20(%esp), %esi
        movl    28(%esp), %ecx
        movl    32(%esp), %ebx
	subl    $16, %esp
        movl    %ecx, %eax
        mull    %esi
        movl    %edx, %edi
        movl    %eax, 12(%esp)
        movl    %ecx, %eax
        mull    40(%esp)
        movl    %edx, %ecx
        movl    %eax, 8(%esp)
        movl    %ebx, %eax
        mull    %esi
        movl    %edx, %ebx
        movl    %eax, %esi
        movl    48(%esp), %eax
        mull    40(%esp)
        addl    %edi, 8(%esp)
        adcl    %ecx, %eax
        adcl    $0, %edx
        addl    %esi, 8(%esp)
        adcl    %ebx, %eax
        adcl    $0, %edx
        pushl   8(%esp)
        pushl   16(%esp)
	testl	%edx, %eax
	jz	onenum
	pushl	$16
	pushl   %edx
        pushl   %eax
        pushl   $form2
        calll	printf
	addl    $16, %esp
	jmp	exit

onenum:
	pushl	$form1
	calll	printf
	addl    $4, %esp

exit:	
	addl    $24, %esp
        popl    %esi
        popl    %edi
        popl    %ebx

	movl    %ebp, %esp
        popl    %ebp
        retl
