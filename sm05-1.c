#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

enum
{
    FRAC_LEN = 23,
    EXP_LEN = 8,
    SIGN_LEN = 1,
};


int main()
{
    union {
        float numb;
        uint32_t bits;
    } my_float;
    while (scanf("%f", &my_float.numb) != EOF) {
        uint32_t frac_mask = (1 << FRAC_LEN) - 1;
        uint32_t exp_mask = (1 << EXP_LEN) - 1;
        uint32_t sign_mask = (1 << SIGN_LEN) - 1;
        uint32_t numb_frac = my_float.bits & frac_mask;
        my_float.bits >>= FRAC_LEN;
        uint32_t numb_exp = my_float.bits & exp_mask;
        my_float.bits >>= EXP_LEN;
        uint32_t numb_sign = my_float.bits & sign_mask;
        printf("%"PRIu32" %"PRIu32" %"PRIx32"\n", numb_sign, numb_exp, numb_frac);
    };
    
    return 0;
}
