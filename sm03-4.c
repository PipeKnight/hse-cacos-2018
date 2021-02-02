#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>

enum
{
    OCTET_AMOUNT = 16,
    BYTES_TO_BIN = 8,
    SIZE_OF_OCTET = 4
};

int main()
{
    uint32_t octet = 0, data_counter = 0, counter = 0, current_octet;
    while (scanf("%" SCNx32, &current_octet) != EOF) {
        counter++;
        if (counter % (OCTET_AMOUNT + 1) == 1) {
            continue;
        }
        data_counter++;
        octet = (octet << BYTES_TO_BIN) + current_octet;
        if (data_counter % SIZE_OF_OCTET == 0) {
            printf("%" PRIu32 "\n", octet);
            octet = 0;
            data_counter = 0;
        }
    }
    return 0;
}
