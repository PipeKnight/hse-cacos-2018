#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main() {
    int32_t first, last = 0, current;
    uint32_t max_dist = 0;
    int were_two_numb = 0;
    while (scanf("%" SCNd32, &current) != EOF) {
        if (were_two_numb == 0) {
            first = current;
            were_two_numb = 1;
        } else if (current >= last) {
            uint32_t dist = (uint32_t) current - (uint32_t) first;
            if (dist > max_dist) {
                max_dist = dist;
            }
        } else {
            first = current;
        }
        last = current;
    }
    printf("%" PRIu32 "\n", max_dist);
    return 0;
}
