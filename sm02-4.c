#include <stdio.h>
#include <ctype.h>

enum { NOTATION = 7 };

int main() {
    int curr_symb = 0;
    long double number = 0, seven_pow = 1;
    int there_was_dot = 0;
    int was_printed = -1;
    while (1) {
        curr_symb = getchar();
        int is_septenary = curr_symb >= '0' && curr_symb < '0' + NOTATION;
        if ((is_septenary == 0 && curr_symb != '.') || curr_symb == EOF) {
            if (was_printed == 0) {
                printf("%.10Lf\n", number); 
            }
            seven_pow = 1;
            there_was_dot = 0;
            was_printed = 1;
            number = 0;
            if (curr_symb == EOF) {
                break;
            } else {
                continue;
            }
        }
        if (curr_symb == '.') {
            there_was_dot = 1;
            continue;
        }
        if (there_was_dot == 0) {
            was_printed = 0;
            number = number * NOTATION + (curr_symb - '0');
        } else {
            seven_pow *= NOTATION;
            number += (curr_symb - '0') / seven_pow;
        }
    }
    return 0;
}
