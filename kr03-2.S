        .text
        .global process

process:
        pushl   %ebp
        movl    %esp, %ebp
        pushl   %ebx
        pushl   %edi
        
        movl    8(%ebp), %eax
        movl    12(%ebp), %ebx
        movl    16(%ebp), %ecx

        movl    $4, %edi
        imull   %edi
        jo      overflow
        
        movl    %eax, %edi
        movl    %ebx, %eax
        movl    $-5, %ebx
        imull   %ebx
        jo      overflow

        addl    %edi, %eax
        jo      overflow
        movl    %eax, (%ecx)
        movl    $1, %eax
        jmp     exit


overflow:
        movl    $0, %eax
exit:   
        pop     %edi
        pop     %ebx
        movl    %ebp, %esp
        pop     %ebp
        ret
