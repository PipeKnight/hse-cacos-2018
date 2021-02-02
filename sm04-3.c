#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    for (int i = 1; i != argc; ++i) {
        char *ptr = argv[i];
        char *endptr;
        long int num = strtol(ptr, &endptr, 10);
        int to_prinf = -1;
        if (endptr == ptr || *endptr != '\0') {
            to_prinf = -1;
        } else if (num == (int8_t) num) {
            to_prinf = 1;
        } else if (num == (int16_t) num) {
            to_prinf = 2;
        } else if (num == (int32_t) num) {
            to_prinf = 4;
        }
        printf("%i\n", to_prinf);
    }
    return 0;
}
