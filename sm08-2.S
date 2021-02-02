        .data
A:      .int    0
        .global A
B:      .int    0
        .global B
C:      .int    0
        .global C
D:      .int    0
        .global D
R:      .int    0
        .global R

        .text
        .global process
process:
        movl    A, %eax
        imull   B
        movl    %eax, R
        movl    C, %eax
        imull   D
        subl    %eax, R

        ret

