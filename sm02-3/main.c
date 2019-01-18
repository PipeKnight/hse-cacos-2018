#include <stdio.h>
#include <ctype.h>

int main (void) {
    int c;
    int ans = 0;
    int zero = 0;
    while ((c = getchar_unlocked()) != EOF) {
        if (isdigit(c)) {
            ans += c;
            ++zero;
        }
    }
    printf("%d\n", ans - '0' * zero);
    return 0;
}
