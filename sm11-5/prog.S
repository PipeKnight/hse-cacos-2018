        .text
        .global writeu32
writeu32:
        push    %ebp
        movl    %esp, %ebp
        push    %ebx
        push    %esi
        push    %edi
	
	xorl    %edi, %edi
	xorl    %ebx, %ebx
        xorl    %edx, %edx
	
        cmpl    $0, %ecx
        je	printchar

loop:
	movl	%ecx, %ebx
	call	Div
	movl	%eax, %esi
	movl	$10, %edi
	mull	%edi
	movl	%ebx, %edx
	subl	%eax, %edx
	call	printchar
	movl	%esi, %ecx
	cmpl    $0, %ecx
        je	exit
	jmp	loop

printchar:
        addl    $'0', %edx
        push    %edx
        push    %ecx
        movl    stout, %edx
        movl    4(%esp), %ecx
        call    writechar
        popl    %ecx
        popl    %edx
	ret

exit:
	popl    %edi
        popl    %esi
        popl    %ebx
        movl    %ebp, %esp
        popl    %ebp
        ret

Div: // source: godbolt
        movl    $-858993459, %edx
        movl    %edx, %eax
        mull    %ebx
        movl    %edx, %eax
        shrl    $3, %eax
        ret