#include<inttypes.h>

uint32_t satsum(uint32_t v1, uint32_t v2) {
    uint32_t result = 0;
    if (__builtin_add_overflow(v1, v2, &result)) {
        return ~((uint32_t) 0);
    }
    return result;
}
