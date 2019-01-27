#include <stdio.h>
#include <stdint.h>

enum { MANT = 23, NONE = -1 };

int checkprecise(uint32_t a) {
    int first = NONE;
    int last = NONE;
    int i = 0;
    while (a > 0) {
        if (a & 1) {
            if (first == NONE) {
                first = i;
            }
            last = i;
        }
        ++i;
        a >>= 1;
    }
    return (last - first <= MANT);
}

int main() {
    uint32_t a = 0;
    while (scanf("%u", &a) != EOF) {
        printf("%d\n", checkprecise(a));
    }
    return 0;
}
