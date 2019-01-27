#include <stdint.h>

#define INTMAX (((uint32_t)(-1)) >> 1)

int32_t satsum(int32_t v1, int32_t v2) {
    int32_t sum;
    if (__builtin_add_overflow(v1, v2, &sum)) {
        if (v1 > 0) {
            return INTMAX;
        }
        return ~INTMAX;
    } else {
        return sum;
    }
}
