        .text
        .global A
        .global B
        .global C
        .global process
process:
        pushl   %ebp
        movl    %esp, %ebp

        movsd   A, %xmm0
        movsd   B, %xmm1
        movl    $2, %eax
        cvtsi2sd        %eax, %xmm3

        addsd   %xmm1, %xmm0
        divsd   %xmm3, %xmm0

        movsd   %xmm0, C

        movl    %ebp, %esp
        popl    %ebp
        ret



