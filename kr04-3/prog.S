        .text
one:    .double 1
mone:	.double -1
        .global myexpm2
myexpm2:
        push    %ebp
        movl    %esp, %ebp
	
        movsd   one, %xmm0	// result
        movsd   8(%ebp), %xmm1
	mulsd   %xmm1, %xmm1
	mulsd	mone, %xmm1	// %xmm1 = -x^2
        movsd   one, %xmm3	// current addendum
        movsd   one, %xmm4	// divisor (for factorial)
        movsd   one, %xmm5	// increment
loop:
        movsd   %xmm0, %xmm2	// temp thing for comparison
        mulsd   %xmm1, %xmm3
        divsd   %xmm4, %xmm3
        addsd   %xmm3, %xmm2    
        comisd  %xmm0, %xmm2
        je      exit
        movsd   %xmm2, %xmm0
        addsd   %xmm5, %xmm4
        jmp     loop
exit:
        movl    16(%ebp), %eax	// pointer to r
        movsd   %xmm0, (%eax)
	
        movl    %ebp, %esp
        popl    %ebp
        ret  
  