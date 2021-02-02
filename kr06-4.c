#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main() {
    unsigned long sum_wr = 0, sum_ex = 0;
    while (1) {
        uint32_t begin, end;
        if (scanf("%" SCNx32 "-%" SCNx32, &begin, &end) == EOF) {
            break;
        }
        char rights[5];
        scanf("%4s", rights);
        if (rights[2] == 'x') {
            sum_ex += (end - begin);
        }
        if (rights[1] == 'w') {
            sum_wr += (end - begin);
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
    printf("%lu\n%lu\n", sum_wr, sum_ex);
    return 0;
}
