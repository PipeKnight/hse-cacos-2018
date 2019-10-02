#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

uint64_t mulmod(uint64_t a, uint64_t b, uint64_t c) {
    if (b == 0) {
        return 0;
    }
    a %= c;
    b %= c;
    uint64_t res = 0;
    uint64_t t = 0;
    if (b % 2) {
        t = mulmod(a, b - 1, c);
        if (__builtin_add_overflow(t, a, &res)) {
            res = t + a - c;
        }
        return res % c;
    }
    if (__builtin_add_overflow(a, a, &res)) {
        res = a + a - c;
    }
    res %= c;
    return mulmod(res, b / 2, c) % c;
}