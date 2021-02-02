#include <stdio.h>
#include <ctype.h>

int main()
{
    int current_symb = 0;
    int sum = 0;
    while (current_symb != EOF) {
        current_symb = getchar_unlocked();
        if (isdigit(current_symb)) {
            sum += current_symb - '0';
        }
    }
    printf("%i\n", sum);
    return 0;
}
