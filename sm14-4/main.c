#include <stdio.h>

int main() {
    unsigned long long st, fn, res = 0;
    while (scanf("%llx-%llx %*[^\n]", &st, &fn) == 2) {
        res += fn - st;
    }
    printf("%llu\n", res);
    return 0;
}
