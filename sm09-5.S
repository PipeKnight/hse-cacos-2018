        .text
        .global process
process:
        pushl   %ebp
        movl    %esp, %ebp
        
        pushl   $1
        pushl   print_par

        call    scanf
        call    printf

        movl    %ebp, %esp
        pop     %ebp
print_par:
        .asciz  "%d"
