        .text
        .global satsum
satsum:
        pushl   %ebp
        movl    %esp, %ebp

        movl    8(%ebp), %eax
        add     12(%ebp), %eax

        jnc     exit
        movl    $~0, %eax
exit:
        movl    %ebp, %esp
        pop     %ebp
        ret
