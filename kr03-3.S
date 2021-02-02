        .text
        .global mystrspn

mystrspn:
        pushl   %ebp
        movl    %esp, %ebp
        pushl   %esi
        pushl   %edi
        pushl   %ebx

        movl    8(%ebp), %ecx
        movl    12(%ebp), %edx

        xorl    %eax, %eax

        movzb   (%ecx), %esi
        movl    %edx, %ebx
        jmp     count

next_s:
        testl   %esi, %esi
        jz      exit
        incl    %ecx
        movzb   (%ecx), %esi
        movl    %edx, %ebx
        jmp     count

count:
        movzb   (%ebx), %edi
        testl   %edi, %edi
        jz      exit
        incl    %ebx 
        
        cmpl    %esi, %edi
        jnz     count
        incl    %eax
        jmp     next_s


exit:
        popl    %ebx
        popl    %edi
        popl    %esi
        movl    %ebp, %esp
        popl    %ebp
        ret

param:
        .asciz  "%s\n"
