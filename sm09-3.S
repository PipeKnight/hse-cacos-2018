        .text
        .global mystrcmp

mystrcmp:
        pushl   %ebp
        movl    %esp, %ebp
        pushl   %ebx
        
        movl    8(%ebp), %ecx
        movl    12(%ebp), %edx

loop:
        movzb   (%ecx), %eax
        movzb   (%edx), %ebx

        incl    %ecx
        incl    %edx
        
        subl    %ebx, %eax
        jnz     exit
        cmpl    $0, %ebx
        jnz     loop

exit:
        pop     %ebx
        pop     %ebp
        ret

