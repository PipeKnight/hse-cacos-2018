#include <stdio.h>
#include <stdlib.h>

int binp(int a, int b, int mod) {
    if (b == 0) {
        return 1;
    }
    if (b % 2) {
        return (binp(a, b - 1, mod) * a) % mod;
    }
    return (binp(a, b / 2, mod) * binp(a, b / 2, mod)) % mod;
}

int main()
{
    int n, i, j;
    scanf("%d", &n);
    int rev[n];
    for (i = 0; i < n; ++i) {
        rev[i] = binp(i, n - 2, n);
    }
    for (i = 0; i < n; ++i) {
        for (j = 1; j < n; ++j) {
            printf("%d ", (i * rev[j]) % n);
        }
        putchar('\n');
    }
}