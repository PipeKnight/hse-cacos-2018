        .text
        .global main
main:
        call    readi32
        movl    %eax, %ebx
        jmp     loop
        call    finish
loop:
        cmpl    $0, %ebx
        jl      exit
        movl    %ebx, %eax
        call    writei32
        call    nl
        decl    %ebx
        jmp     loop

exit:
        call    finish
