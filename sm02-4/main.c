#include <stdio.h>
#include <ctype.h>
#include <math.h>

enum { OUT = 0, INT = 1, FRAC = 2, BASE = 7 };

int main () {
    int c;
    int power = 0;
    int state = OUT;
    double numI = 0;
    double numD = 0;
    while ((c = getchar()) != EOF) {
        if (state == OUT) {
            if ('0' <= c && c < '0' + BASE) {
                state = INT;
                numI = c - '0';
            }
            if (c == '.') {
                state = FRAC;
                power = 0;
                numI = 0;
                numD = 0;
            }
        }
        else if (state == INT) {
            if ('0' <= c && c < '0' + BASE) {
                numI = BASE * numI + c - '0';
            }
            else if (c == '.') {
                state = FRAC;
                power = 0;
                numD = 0;
            }
            else {
                printf("%.10g\n", numI);
                state = OUT;
                numI = 0;
                numD = 0;
            }
        }
        else if (state == FRAC) {
            if ('0' <= c && c < '0' + BASE) {
                ++power;
                numD += (c - '0') * pow(BASE, -power);
            }
            else {
                printf("%.10g\n", numI + numD);
                state = OUT;
                numI = 0;
                numD = 0;
            }
        }
    }
    if (state == INT) {
        printf("%.10g\n", numI);
    }
    if (state == FRAC) {
        printf("%.10g\n", numI + numD);
    }
    return 0;
}
