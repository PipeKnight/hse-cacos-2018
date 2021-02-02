        .text
        .global forward.args

forward.args:
        pushl   %ebp
        movl    %esp, %ebp
        pushl   %ebx

        movl    8(%ebp), %eax
        movl    12(%ebp), %edx // edx, eax = v1
        movl    16(%ebp), %ebx
        movl    20(%ebp), %ecx

        pushl   %edx
        pushl   %eax
        pushl   %ebx
        pushl   %ecx

        call    process
        addl    $16, %esp
        
        notl    %eax

        popl    %ebx
        movl    %ebp, %esp
        popl    %ebp
        ret
