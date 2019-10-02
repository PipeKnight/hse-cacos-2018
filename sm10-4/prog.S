        .data
        .text
        .global dot_product

dot_product:
	push    %ebp
        movl    %esp, %ebp
	
        pushl   %edi
        pushl   %esi
        pushl   %ebx
        movl    20(%esp), %ebx
        movl    24(%esp), %esi
        movl    28(%esp), %edi
	movl    $0, %edx
        pxor    %xmm0, %xmm0
	pxor    %xmm1, %xmm1
        testl   %ebx, %ebx
        jz	exit
        

loop:
        movd    (%esi,%edx,4), %xmm1
        movd	(%edi,%edx,4), %xmm2
	mulss   %xmm2, %xmm1
        addss	%xmm1, %xmm0
        incl    %edx
        cmpl    %edx, %ebx
        jne     loop

exit:
	sub     $4, %esp
        movd	%xmm0, (%esp)
        fld	(%esp)
        add     $4, %esp
	
        popl    %ebx
        popl    %esi
        popl    %edi

	movl    %ebp, %esp
        popl    %ebp
        ret
