#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum { NUM = 10, ALP = 26, LAST_SYMBOL = 63 };

int main()
{
    int c = 0;
    int uc = 0;
    while ((c = getchar_unlocked()) != EOF) {
        if (isalnum(c)) {
            if (isdigit(c)) {
                uc = c - '0' + 1;
            }
            else if (islower(c)) {
                uc = c - 'a' + NUM + 1;
            }
            else if (isupper(c)) {
                uc = c - 'A' + NUM + ALP + 1;
            }
            //printf("%u %d ", uc, c);
            uc ^= (1 << 3);
            uc &= ((~0) - (1 << 2));
            if (uc == 0) {
                putchar('@');
            }
            else if (uc <= NUM) {
                putchar(uc - 1 + '0');
            }
            else if (uc <= NUM + ALP) {
                putchar(uc - NUM - 1 + 'a');
            }
            else if (uc <= LAST_SYMBOL - 1) {
                putchar(uc - NUM - ALP - 1 + 'A');
            }
            else if (uc == LAST_SYMBOL) {
                putchar('#');
            }
            //printf("\n");
        }
    }
}