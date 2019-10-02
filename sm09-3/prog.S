	.global 	mystrcmp
mystrcmp:
        pushl   %ebp
        movl    %esp, %ebp

	and     $-16, %esp
        sub     $16, %esp
		
        xorl    %ecx, %ecx
	xorl    %eax, %eax
	xorl    %edx, %edx

compare:
        movl    8(%ebp), %eax
        movl    12(%ebp), %edx
        movzbl  (%eax,%ecx), %eax // mov zero extend byte to long
        movzbl  (%edx,%ecx), %edx // from [edx+ecx] to edx
        testb   %al, %al
        je      exit
        incl    %ecx
        cmpb    %dl, %al
        je      compare

exit:
        subl    %edx, %eax
		
        movl    %ebp, %esp
        popl    %ebp
        ret
