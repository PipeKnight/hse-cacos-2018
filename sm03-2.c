#include<inttypes.h>

int32_t satsum(int32_t v1, int32_t v2) {
    int32_t result = 0;
    if (__builtin_add_overflow(v1, v2, &result)) {
        if (v1 > 0) {
            return (~((uint32_t) 0)) >> 1;
        } else {
            return ~((~((uint32_t) 0)) >> 1);
        }
    }
    return result;
}
