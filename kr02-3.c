#include <stdint.h>
#include <string.h>
#include <stdio.h>

union MyFloat
{
    struct
    {
        uint32_t mantissa : 23;
        uint32_t expon : 8;
        uint32_t sing : 1;
    };
    uint32_t bits;
    float value;
};

int cmpf(const void *p1, const void *p2) {
    union MyFloat f1;
    union MyFloat f2;
    memcpy(&f1.value, p1, sizeof(f1.value));
    memcpy(&f2.value, p2, sizeof(f2.value));
    if (f1.bits == f2.bits) {
        return 0;
    }
    if (f1.sing > f2.sing) {
        return -1;
    }
    if (f1.sing < f2.sing) {
        return 1;
    }
    int cmp_res = f1.bits < f2.bits ? -1 : 1;
    if (f1.sing == 1) {
        cmp_res *= -1;
    }
    return cmp_res;
}
