#include <stdio.h>
#include <stdlib.h>

const double EPS = 0;

int check(double x, double y) {
    if (2 - EPS <= x && x <= 5 + EPS) {
        if (1 - EPS <= y && y <= 7 + EPS) {
            if (x - 2 - EPS <= y && y <= x + 3 + EPS) {
                if (((int)x) >= 2 && ((int)x) <= 5) {
                    if (((int)y) >= 1 && ((int)y) <= 7) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int main()
{
    double x, y;
    scanf("%lf\n%lf", &x, &y);
    printf("%d", check(x, y));
    return 0;
}