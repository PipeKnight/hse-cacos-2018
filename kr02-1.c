#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
 
 
int main()
{
    uint32_t numb;
    int the_first = 1;
    uint32_t current_set = 0;
    uint32_t result = 0;
    while (scanf("%" SCNu32, &numb) != EOF) {
        if (numb != 0) {
            numb--;
            current_set |= (1u << numb);
        } else {
            if (the_first == 0) {
                result = ~(result ^ current_set);
            } else {
                result = current_set;
                the_first = 0;
            }
            current_set = 0;
        }
    }
    printf("%" PRIx32 "\n", result);
    return 0;
}
