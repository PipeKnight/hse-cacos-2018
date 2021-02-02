        .text
        .global process

process:
        pushl   %ebp
        movl    %esp, %ebp
        pushl   %ebx
        pushl   %esi
        pushl   %edi

        movl    8(%ebp), %ebx

        movl    (%ebx), %eax
        imull   12(%ebx)

        movl    %eax, %esi
        movl    %edx, %edi
        
        movl    4(%ebx), %eax
        imull   8(%ebx)

        subl    %eax, %esi
        sbbl    %edx, %edi

        movl    %esi, %eax
        movl    %edi, %edx

        popl    %edi
        popl    %esi
        popl    %ebx
        movl    %ebp, %esp
        popl    %ebp
        ret
        

