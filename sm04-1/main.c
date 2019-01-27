#include <stdio.h>

enum { SIGN = 1, EXP = 8, MANT = 23 };

typedef union
{
    unsigned b;
    float a;
} FloatBits;

int main() {
    float a = 0;
    while (scanf("%f", &a) != EOF) {
        FloatBits u;
        u.a = a;
        printf("%d %d %x\n", u.b >> (EXP + MANT), (u.b >> MANT) & ((1 << EXP) - 1), u.b & ((1 << MANT) - 1));
    }
    return 0;
}