        .text
        .global tree_find
        .global admiss
tree_find:
        pushl   %ebp
        movl    %esp, %ebp
        pushl   %ebx
        movl    8(%ebp), %ebx  // ebx = root
        movsd   12(%ebp), %xmm0 // xmm0 = key
        movl    20(%ebp), %ecx   // ecx = pstr
        
loop:   
        testl   %ebx, %ebx
        jz      not_found
        movsd   (%ebx), %xmm1 // xmm1 = current node key
        movsd   %xmm0, %xmm2
        movsd   %xmm1, %xmm3
        maxsd   %xmm0, %xmm3
        minsd   %xmm1, %xmm2
        /*
        xmm2 -- min(key, curr key)
        xmm3 -- max(key, curr key)
        */
        subsd   %xmm2, %xmm3
        comisd  admiss, %xmm3
        jc      found
        
        comisd  %xmm1, %xmm0
        jc      to_left
        jmp     to_right

to_left:
        movl    8(%ebx), %ebx
        jmp     loop
to_right:
        movl    12(%ebx), %ebx
        jmp     loop
found:
        movl    $1, %eax
        testl   %ecx, %ecx
        jz      exit
        movl    16(%ebx), %edx
        movl    %edx, (%ecx)
        jmp     exit
not_found:
        movl    $0, %eax
exit:
        pop     %ebx
        movl    %ebp, %esp
        pop     %ebp
        ret
admiss:
        .double 1e-8
