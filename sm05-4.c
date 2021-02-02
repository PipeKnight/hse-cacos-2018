#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

enum { BIT = 8 };

uint32_t fixed_mul(uint32_t a, uint32_t b, int n) {
    if (n == 0) {
        uint32_t result;
        if (__builtin_mul_overflow(a, b, &result)) {
            return -1;
        } else {
            return result;
        }
    }
    uint64_t result = (uint64_t) a * (uint64_t) b;
    result >>= (n - 1);
    
    result >>= 1;
    if (result >> (sizeof(a) * BIT) > 0) {
        return -1;
    } else {
        return result;
    }

}
