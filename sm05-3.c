#include <stdint.h>
#include <assert.h>
#include <math.h>	

union FloatParts
{
    float value;
    struct
    {
        uint32_t mantis : 23;
        uint32_t expon : 8;
        uint32_t sign : 1;
    };
};

FPClass fpclassf(float value, int *psign) {
    union FloatParts numb;
    numb.value = value;
    *psign = numb.sign;
 
    if (numb.mantis == 0 && numb.expon == 0) {
        return FFP_ZERO;
    }
    if (numb.mantis > 0 && numb.expon == 0) {
        return FFP_DENORMALIZED;
    }
    if (numb.mantis > 0 && numb.expon == (uint8_t) -1) {
        *psign = 0;
        return FFP_NAN;
    }
    if ((numb.expon == (uint8_t) -1) && (numb.mantis == 0)) {
        return FFP_INF;
    }
    return FFP_NORMALIZED;
}
