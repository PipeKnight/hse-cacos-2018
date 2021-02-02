#include <stdio.h>

int main()
{
    long long a, b;
    int n;
    scanf("%lld%lld%i", &a, &b, &n);
    printf("%*s", n, "");
    for (long long i = a; i != b; ++i) {
        printf(" %*lld", n, i);
        if (i == b - 1) {
            printf("\n");
        }
    }
    for (long long i = a; i != b; ++i) {
        printf("%*lld ", n, i);
        for (long long j = a; j != b; ++j) {
            printf("%*lld", n, i * j);
            if (j != b - 1) {
                printf(" ");
            } else {
                printf("\n");
            }
        }
    }
    return 0;
}
