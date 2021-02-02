#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

enum
{
    NOTATION = 8
};

int main()
{
    unsigned long long m;
    scanf("%llu", &m);
    unsigned long long min_mod = m;
    int mod_was_init = 0;
    unsigned long long curr_numb = 0;
    int symb = 0;
    while (1) {
        symb = getchar();
        if (isdigit(symb) && symb < '0' + NOTATION) {
            mod_was_init = 1;
            curr_numb = curr_numb * NOTATION % m + (symb - '0') % m;
        } else {
            if (mod_was_init != 0 && curr_numb % m < min_mod) {
                min_mod = curr_numb % m;
            }
            mod_was_init = 0;
            curr_numb = 0;
        }
        if (symb == EOF) {
            break;
        }
    }
    printf("%lld\n", min_mod);
    return 0;
}
