        .text
        .global list_del
list_del:
        pushl   %ebp
        movl    %esp, %ebp

        pushl   %ebx
        pushl   %esi
        pushl   %edi

        xorl    %ecx, %ecx // last node
        movl    8(%ebp), %edi // edi = current node(head)
        movl    12(%ebp), %esi // esi = value
        movl    %edi, %eax

loop:
        testl   %edi, %edi
        jz      exit

        movzb   (%edi), %ebx
        movsbl  %bl, %ebx

        cmpl    %ebx, %esi
        jz      delete_node
        movl    %edi, %ecx
        movl    4(%edi), %edi
        jmp     loop

delete_node:
        testl   %ecx, %ecx
        jz      refresh_begin
        movl    4(%edi), %edi
        movl    %edi, 4(%ecx)
        jmp     loop
refresh_begin:
        movl    4(%edi), %edi
        movl    %edi, %eax
        jmp     loop


exit:
        popl    %edi
        popl    %esi
        popl    %ebx
        movl    %ebp, %esp
        popl    %ebp
        ret