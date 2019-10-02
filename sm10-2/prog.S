	.text
	.global myhypot
myhypot:
	push    %ebp
        movl    %esp, %ebp
	
        movl    24(%esp), %eax
        movsd   16(%esp), %xmm0
        movsd   8(%esp), %xmm1
        mulsd   %xmm1, %xmm1
        mulsd   %xmm0, %xmm0
        addsd   %xmm1, %xmm0
	sqrtsd  %xmm0, %xmm0
        movsd   %xmm0, (%eax)

	movl    %ebp, %esp
        popl    %ebp
        ret