#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

enum { SEVENBITS = 127, LENGTH = 7 };

int main()
{
    uint32_t a = 0;
    while (scanf("%" SCNu32, &a) != EOF) {
        if (a == 0) {
            printf("00\n");
            continue;
        }
        while (a != 0) {
            int octet = a & SEVENBITS;
            a >>= LENGTH;
            if (a != 0) {
                octet |= (SEVENBITS + 1);
                printf("%0*x ", 2, octet);
            }
            else {
                printf("%0*x\n", 2, octet);
            }
        }
    }
    return 0;
}
