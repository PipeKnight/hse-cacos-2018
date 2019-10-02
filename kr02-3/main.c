#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    char *pEnd = NULL;
    int cnum;
    long long Min, Max;
    for (int i = 1; i < argc; i++) {
        pEnd = NULL;
        cnum = strtol(argv[i], &pEnd, 10);
        pEnd = argv[i];
        Min = cnum;
        Max = cnum;
        while (*pEnd) {
            int prev = pEnd - argv[i];
            cnum = strtol(pEnd, &pEnd, 10);
            int cur = pEnd - argv[i];
            if (cur == prev) {
                break;
            }
            if (cnum < Min) {
                Min = cnum;
            }
            if (cnum > Max) {
                Max = cnum;
            }
            if (i != argc - 1 && *pEnd != ',') {
                break;
            }
            ++pEnd;
        }
        printf("%lld\n", Max - Min + 1);
    }
    return 0;
}

