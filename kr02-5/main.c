#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

enum { MANT = 10, EXP = 5, BIAS = 15 };

uint64_t myabs(int value) {
    return (value < 0) ? -((uint64_t)value) : (uint64_t)value;
}

void to_half_float(int value, unsigned short *hf) {
    if (value == 0) {
        *hf = 0;
        return;
    }
    int sign = value < 0;
    int frac = 0, exp = 0;
    int length = -1;
    int max_exp = (1 << EXP) - 1;
    uint64_t val, t;
    t = val = myabs(value);
    while (t) {
        t = t >> 1;
        ++length;
    }
    exp = length + BIAS;
    if (exp >= max_exp) {
        exp = max_exp;
    } else {
        if (length > MANT) {
            int diff = length - MANT;
            int mant_bits = 1 << MANT;
            frac = val >> diff;
            frac &= mant_bits - 1;
            if ((val >> (diff - 1)) & 1) {
                ++frac;
            }
            if (frac >= mant_bits && exp >= max_exp - 1) {
                exp = max_exp;
                frac = 0;
            }
        } else {
            frac = (val) & ((1 << length) - 1);
            frac <<= MANT - length;
        }
    }
    *hf = sign;
    *hf <<= EXP;
    *hf += exp;
    *hf <<= MANT;
    *hf += frac;
}
