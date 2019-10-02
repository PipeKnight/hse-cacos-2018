#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

enum { MANT = 52, NONE = -1 };

uint64_t myabs(int64_t value) {
    return (value < 0) ? -((uint64_t)value) : (uint64_t)value;
}

int checkprecise(int64_t b) {
    uint64_t a = myabs(b);
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
    int64_t a = 0;
    while (scanf("%lld", &a) != EOF) {
        printf("%d\n", checkprecise(a));
    }
    return 0;
}
