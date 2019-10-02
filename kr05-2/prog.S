	.text
	.global process
process:
        movl    8(%esp), %eax
        movl    4(%esp), %ecx
        movl    (%ecx), %edx
        movsd   (%edx,%eax,8), %xmm0
        movl    $3, %edx
        subl    %eax, %edx
        subsd   4(%ecx,%edx,8), %xmm0
        mulsd   %xmm0, %xmm0
        movsd   %xmm0, 36(%ecx)
        retl