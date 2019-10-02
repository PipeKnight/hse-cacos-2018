        .text
        .global forward.args
forward.args:
        push    %ebp
        movl    %esp, %ebp
	andl	$-16, %esp
        push    %ebx
	
        movl    8(%ebp), %eax
        movl    12(%ebp), %ebx
        movl    16(%ebp), %ecx
        movl    20(%ebp), %edx
        push    %ebx
        push    %eax
        push    %ecx
        push    %edx
        call    process
        addl    $16, %esp
        notl    %eax

        popl    %ebx
        movl    %ebp, %esp
        popl    %ebp
        ret