#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, w;
    scanf("%d%d", &n, &w);
    int N = 1;
    int i = 0;
    int j = 0;
    N <<= n;
    for (i = 0; i < N; ++i, ++j) {
        if (i == N / 2) {
            j = -(N / 2);
        }
        printf("|%*x|%*u|%*d|\n", w, i, w, i, w, j);
    }
}