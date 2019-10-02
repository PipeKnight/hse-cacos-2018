_form:
	.asciz 	"%d"
_form2:
	.asciz	"%d "
_nl:  
        .asciz 	"\n"
        .text
        .global process


process:
        push    %ebp
        movl    %esp, %ebp
	
        subl    $8, %esp
        leal    -4(%ebp), %eax
        movl    $0, -8(%ebp)
        push    %eax
        push    $_form
        call    scanf
        addl    $8, %esp
	movl	-4(%ebp), %edx
        cmpl    $0, %edx
	
        jz      exit
read:
        subl    $4, %esp
        leal    (%esp), %eax
        push    %eax
        push    $_form
        call    scanf
        addl    $8, %esp
        incl    -8(%ebp)
        movl    -8(%ebp), %eax
	movl	-4(%ebp), %edx
        cmpl    %eax, %edx
        jnz     read

        movl    $0, -8(%ebp)

write:
        push    $_form2
        call    printf
        addl    $8, %esp
        incl    -8(%ebp)
        movl    -8(%ebp), %eax
	movl	-4(%ebp), %edx
        cmpl    %eax, %edx
        jnz     write

exit:
        push    $_nl
        call    printf

	xorl	%eax, %eax
	xorl	%edx, %edx
        movl    %ebp, %esp
        popl    %ebp
        ret

