        .text
        .global A
        .global B
        .global print_fib

print_fib:
        pushl   %ebp
        movl    %esp, %ebp

        movl    A, %eax
        addl    B, %eax

        movl    B, %ecx
        addl    %eax, %ecx

        movl    %eax, %edx
        addl    %ecx, %edx

        pushl   %edx
        pushl   %ecx
        pushl   %eax
        pushl   $print_param
        call    printf

        movl    %ebp, %esp
        popl    %ebp
        
        ret

print_param:
        .asciz  "%d %d %d\n"
