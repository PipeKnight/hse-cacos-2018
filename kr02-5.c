#include <stdint.h>
#include <stdlib.h>

void to_half_float(int value, unsigned short *hf) {
    union
    {
        struct
        {
            int16_t mant : 10;
            int16_t epxon : 5;
            int16_t sign : 1;
        };
        int16_t bits;
    } half_f;
    half_f.sign = value < 0;
    value = abs(value);
    
}
