        .text
        .global main
main:
        xorl    %ebx, %ebx
        xorl    %esi, %esi

loop:
        call    readi32
        jc      exit
        testl   $1, %eax
        jnz     add_od
add_ev:
        addl    %eax, %ebx
        jmp     loop
add_od:
        addl    %eax, %esi
        jmp     loop
    
exit:
        movl    %ebx, %eax
        call    writei32
        call    nl
        movl    %esi, %eax
        call    writei32
        call    nl
        call    finish
                
