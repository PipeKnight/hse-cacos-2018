#include <stdio.h>
#include <wctype.h>
#include <locale.h>
#include <wchar.h>

int main() {
    setlocale(LC_ALL, "");
    wint_t wsymb;
    int dig = 0, big = 0, small = 0;
    while ((wsymb = getwchar()) != WEOF) {
        if (iswdigit(wsymb)) {
            dig++;
        } else if (iswupper(wsymb)) {
            big++;
        } else if (iswlower(wsymb)) {
            small++;
        }
    }
    printf("%d\n%d\n%d\n", dig, big, small);
}
