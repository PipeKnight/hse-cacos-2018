#include <stdio.h>

int main (void) {
    int a, b, c;
    scanf("%d %d", &a, &b);
    while (scanf("%d", &c) != EOF) {
        if (a > b) {
            if (c > a) {
                b = a;
                a = c;
            } else if (c > b) {
                b = c;
            }
        } else {
            if (c > b) {
                a = b;
                b = c;
            } else if (c > a) {
                a = c;
            }
        }
    }
    printf("%d\n", a * b);
    return 0;
}
