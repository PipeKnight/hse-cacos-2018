        .data
P:      .int    0
        .global P
Q:      .int    0
        .global Q
R:      .int    0
        .global R
Z:      .int    0
        .global Z
       
        .text
        .global process
process:
        pushl   %ebp
        movl    %esp, %ebp
 
        pushl   %edi
        pushl   %esi
         
        movl    P, %eax
 
        movl    Z, %esi
        imul    %esi
        imul    %esi
        imul    %esi
 
        movl    %eax, %edi
        movl    Z, %eax
        imull   Q
 
        addl    %eax, %edi
        addl    R, %edi
        movl    %edi, %eax
 
        popl    %esi
        popl    %edi 
        movl    %ebp, %esp
        popl    %ebp
        ret
