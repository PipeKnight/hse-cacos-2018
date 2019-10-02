#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "");
    wchar_t w;
    //wint_t w;
    int up = 0;
    int low = 0;
    int num = 0;
    while ((w = getwchar()) != WEOF) {
        if (iswdigit(w)) {
            ++num;
        }
        else if (iswupper(w)) {
            ++up;
        }
        else if (iswlower(w)) {
            ++low;
        }
    }
    printf("%d\n%d\n%d\n", num, up, low);
    return 0;
}