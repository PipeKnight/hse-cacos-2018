#include <stdio.h>

int main (void) {
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    printf("%*.0s ", n, "");
    for (int i = a; i < b; ++i) {
        printf("%*d", n, i);
        if (i != b - 1) {
            printf(" ");
        }
    }
    printf("\n");
    for (long i = a; i < b; ++i) {
        printf("%*ld ", n, i);
        for (long j = a; j < b; ++j) {
            printf("%*ld", n, i * j);
            if (j != b - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
