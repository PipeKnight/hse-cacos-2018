#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

enum { SZ = 32 };

uint32_t fixed_mul(uint32_t a, uint32_t b, int n) {
    uint64_t res;
    res = (1ULL * a) * b;
    if (((res >> n) >> SZ) != 0) {
        return ~0;
    }
    if (n == 0) {
        return res;
    }
    if (((res >> (n - 1)) & 1) == 1) {
        if ((res & ((1ULL << (n - 1)) - 1)) == 0) {
            if (((res >> n) & 1) == 1) {
                if (__builtin_add_overflow(res, 1ULL << n, &res)) {
                    return ~0;
                }
            }
        }
        else {
            if (__builtin_add_overflow(res, 1ULL << n, &res)) {
                return ~0;
            }
        }
    }
    if (((res >> n) >> SZ) != 0) {
        return ~0;
    }
    return (res >> n);
}
