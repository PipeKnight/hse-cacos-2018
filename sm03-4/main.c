#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

enum { SHIFT = 8, LINE = 4, OCTETS = 4 };

int main()
{
    uint32_t addr = 0;
    while (scanf("%" SCNx32, &addr) != EOF) {
        uint32_t c1, c2, c3, c4;
        for (int i = 0; i < LINE; ++i) {
            if (scanf("%" SCNx32 "%" SCNx32 "%" SCNx32 "%" SCNx32, &c1, &c2, &c3, &c4) != OCTETS) {
                return 0;
            }
            printf("%" PRIu32 "\n", c4 + (c3 << SHIFT) + (c2 << (2 * SHIFT)) + (c1 << (3 * SHIFT)));
        }
    }
    return 0;
}
