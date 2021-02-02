#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

enum { MANTISSA_SIZE = 23 };

int accuracy(uint32_t numb) {
    while (numb != 0 && (numb & 1u) == 0) {
        numb >>= 1;
    }
    return (numb >> (MANTISSA_SIZE + 1)) == 0;
}

int main()
{
    uint32_t numb = 0;
    while (scanf("%" PRIu32, &numb) != EOF) {
        printf("%i\n", accuracy(numb));
    }
    return 0;
}
