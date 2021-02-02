        .text
        .global process

process:
        pushl   %ebp
        movl    %esp, %ebp
        pushl   %ebx
        pushl   %edx
        pushl   %esi
        xorl    %esi, %esi

loop:
        subl    $4, %esp
        pushl   %esp
        pushl   $param_in
        call    scanf
        addl    $8, %esp

        cmpl    $-1, %eax
        jz      exit


        movl    (%esp), %ecx
        movl    %ecx, %edx
        shr     $4, %edx
        shl     $4, %edx
        subl    %edx, %ecx
        cmpl    $9, %ecx
        jz      L1
        cmpl    $10, %ecx
        jz      L2
        addl    (%esp), %esi
        addl    $4, %esp
        jmp     loop

L1:
        movl    (%esp), %ecx
        incl    %ecx
        addl    %ecx, %esi
        addl    $4, %esp
        jmp     loop

L2:
        movl    (%esp), %ecx
        shl     %ecx
        addl    %ecx, %esi
        addl    $4, %esp
        jmp     loop

exit:
        pushl   %esi
        pushl   $param_out
        call    printf
        addl    $12, %esp
        popl    %esi
        popl    %edx
        popl    %ebx
        movl    %ebp, %esp
        popl    %ebp
        ret

param_in:
        .asciz  "%u"

param_out:
        .asciz  "%i\n"
