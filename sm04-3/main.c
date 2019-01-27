#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

enum { SIGN = 1, EXP = 8, MANT = 23 };

typedef union
{
    unsigned b;
    float a;
} FloatBits;

FPClass fpclassf(float value, int *psign) {
    uint32_t exp, frac, sgn;
    FloatBits v;
    v.a = value;
    sgn = v.b >> (EXP + MANT);
    exp = (v.b >> MANT) & ((1 << EXP) - 1);
    frac = v.b & ((1 << MANT) - 1);
    *psign = sgn;
    if ((exp ^ ((1 << EXP) - 1)) == 0) {
        if (frac == 0) {
            return FFP_INF;
        }
        else {
            *psign = 0;
            return FFP_NAN;
        }
    }
    if (exp == 0) {
        if (frac == 0) {
            return FFP_ZERO;
        }
        else {
            return FFP_DENORMALIZED;
        }
    }
    return FFP_NORMALIZED;
}
