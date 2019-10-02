        .text
        .global minmax

minmax:
        push    %ebp
        movl    %esp, %ebp
	push	%esi
	push	%edi
	
	movl	$0, %ecx
	movl	(%eax,%ecx,4), %esi
	movl	(%eax,%ecx,4), %edi
	jmp	loop

loop:	
	incl    %ecx
	cmpl	%ecx, %edx
	jz	end
	cmpl	(%eax,%ecx,4), %esi
	cmovl	(%eax,%ecx,4), %esi
	cmpl	(%eax,%ecx,4), %edi
	cmovg	(%eax,%ecx,4), %edi
	jmp	loop
	
end:
	movl	%esi, %edx
	movl	%edi, %eax
	pop	%edi
	pop	%esi
	movl    %ebp, %esp
        popl    %ebp
        ret