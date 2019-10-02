        .text
        .global tree_find
		
eps:
        .double 1e-8
null:
	.int	0

tree_find:
        push    %ebp
        movl    %esp, %ebp
		
        pushl	%esi
        movl    8(%ebp), %ecx
        movsd   12(%ebp), %xmm0
        movl    20(%ebp), %edx
        movsd   eps, %xmm1
	movl    $0, %eax

search_loop:
        cmpl    null, %ecx
        je      exit
        movsd   (%ecx), %xmm2
        subsd   %xmm0, %xmm2
        movsd   %xmm2, %xmm3
        pslld   $1, %xmm3
        psrld   $1, %xmm3
        comisd  %xmm1, %xmm3
        jbe     key_found
        pxor    %xmm3, %xmm3
        comisd  %xmm2, %xmm3
        ja      right
	jmp	left

left:
        movl    8(%ecx), %esi
        movl    %esi, %ecx
        jmp     search_loop

right:
        movl    12(%ecx), %esi
        movl    %esi, %ecx
        jmp     search_loop

key_found:
        movl    $1, %eax
        cmpl    null, %edx
        je      exit
        movl    16(%ecx), %esi
        movl    %esi, (%edx)

exit:
        popl    %esi
		
        movl    %ebp, %esp
        popl    %ebp
        ret
