        .text
        .global process
        .global compar
process:
        pushl   %ebp
        movl    %esp, %ebp

        pushl   $compar
        pushl   $4
        pushl   12(%ebp)
        pushl   8(%ebp)
        call    qsort
        addl    $16, %esp

        movl    %ebp, %esp
        popl    %ebp
        ret
compar:
        pushl   %ebp
        movl    %esp, %ebp

        pushl   %ebx
        pushl   %esi
        pushl   %edi

        movl    8(%ebp), %esi // first elem
        movl    12(%ebp), %edi // second elem
        

        popcnt  (%edi), %ebx
        popcnt  (%esi), %eax

        subl    %ebx, %eax
        jnz     to_ret
        movl    (%edi), %eax
        movl    (%esi), %ebx
        cmpl    %ebx, %eax
        jb      sub_z
        ja      ab_z
        xorl    %eax, %eax
        jmp     to_ret
sub_z:
        movl    $-1, %eax
        jmp     to_ret
ab_z:
        movl    $1, %eax

to_ret:
        popl    %edi
        popl    %esi
        popl    %ebx
        movl    %ebp, %esp
        popl    %ebp
        ret
