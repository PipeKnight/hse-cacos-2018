        .text
        .global myexp

myexp:
        pushl   %ebp
        movl    %esp, %ebp

        movl    $1, %eax
        cvtsi2sd        %eax, %xmm0
        addsd   8(%ebp), %xmm0
        movsd   8(%ebp), %xmm3

loop:
        movl    $0, %edx
        cvtsi2sd        %edx, %xmm1
        comisd  %xmm1, %xmm3
        jz      exit
        
        incl    %eax
        cvtsi2sd        %eax, %xmm2
        mulsd   8(%ebp), %xmm3
        divsd   %xmm2, %xmm3

        addsd   %xmm3, %xmm0
        jmp     loop

exit:
        movl    16(%ebp), %eax
        movsd   %xmm0, (%eax)
        movl    %ebp, %esp
        popl    %ebp
        ret
