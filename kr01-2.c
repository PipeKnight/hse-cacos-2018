#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>

int main() {
    unsigned int n, w;
    scanf("%d%d", &n, &w);
    uint32_t max_n = 1 << n;
    for (uint32_t i = 0; i != max_n; ++i) {
        printf("|%*" PRIx32, w, i);
        printf("|%*" PRIu32, w, i);
        int32_t temp_i = i;
        if (i >> (n - 1) == 1) {
            temp_i = - ((int32_t) (i - (1 << (n - 1))));
        }
        printf("|%*" PRId32 "|\n", w, temp_i);
    }
    return 0;
}
