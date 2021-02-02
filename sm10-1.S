        .text
        .global process
process:
        pushl   %ebp
        pushl   %ebx
        movl    %esp, %ebp
        
        movl    A, %eax
        movl    A + 4, %ebx
        shl     $1, %eax
        rcl     $1, %ebx

        movl    B, %ecx
        movl    B + 4, %edx
        shr     $1, %edx
        rcr     $1, %ecx
        
        subl    %ecx, %eax
        sbbl    %edx, %ebx

        pushl   %ebx
        pushl   %eax
        pushl   $param
        call    printf 
        
        movl    %ebp, %esp
        popl    %ebx
        popl    %ebp
        ret

param:
        .asciz  "%llu\n"
