        .text
one:	.int	1
zero:	.int	0
        .global addbe
addbe:
        push    %ebp
        movl    %esp, %ebp
        push    %ebx
        push    %esi
        push    %edi
	
        movl    8(%ebp), %edx	// n
        movl    12(%ebp), %ebx	// *pa
        movl    16(%ebp), %esi	// *pb
        movl    20(%ebp), %edi	// *pc
        xorl    %eax, %eax
loop:
        movzbl  -1(%ebx, %edx,), %ecx
        addl    %ecx, %eax
        movzbl  -1(%esi, %edx,), %ecx
        addl    %ecx, %eax
        movl    %eax, %ecx
        shrl    $8, %eax
        movb    %cl, -1(%edi, %edx,)
        decl    %edx
        cmpl    $0, %edx
        jne     loop
exit:
        popl    %edi
        popl    %esi
        popl    %ebx
        movl    %ebp, %esp
        popl    %ebp
        ret