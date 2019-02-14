#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>

typedef union
{
    int8_t o;
    int16_t x;
    int32_t n;
    int64_t bn;
} Num;

int main(int argc, char *argv[])
{
    char *pEnd = NULL;
    long int curnum = 0;
    Num cnum;
    for (int i = 1; i < argc; i++) {
        errno = 0;
        curnum = strtol(argv[i], &pEnd, 10);
        cnum.bn = curnum;
        //printf("%ld %ld %d\n", curnum, cnum.n, errno);
        if (!*argv[i] || *pEnd || errno || cnum.bn != cnum.n) {
            putchar('-');
            putchar('1');
        } else {
            if (cnum.o == cnum.n) {
                putchar('1');
            } else if (cnum.x == cnum.n) {
                putchar('2');
            } else {
                putchar('4');
            }
        }
        putchar('\n');
    }
    return 0;
}