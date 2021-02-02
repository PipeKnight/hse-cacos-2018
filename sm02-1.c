#include<stdio.h>

int main()
{
    unsigned int max1 = 0, max2 = 0, number;
    while (scanf("%u", &number) != EOF) {
        if (number >= max1) {
            max2 = max1;
            max1 = number;
        }
        if (number < max1 && number >= max2) {
            max2 = number;
        }
    }
    printf("%u\n", max1 * max2);
    return 0;
}
