        .text
        .global main
main:
        xorl    %ebx, %ebx
loop:
        call    readi32
        jc      exit
        addl    %eax, %ebx
        jno     loop
overflow:
        shr     $31, %eax
        addl    $2147483647, %eax
        movl    %eax, %ebx
exit:
        movl    %ebx, %eax
        call    writei32
        call    nl
        call    finish

