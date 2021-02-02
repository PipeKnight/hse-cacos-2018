#include <ctype.h>

int mystrdigcmp(const char *str1, const char *str2) {
    while (1) {
        while (isdigit(*str1)) {
            str1++;
        }
        while (isdigit(*str2)) {
            str2++;
        }
        if (*str1 != *str2 || *str1 == '\0') {
            break;
        } else {
            ++str1;
            ++str2;
        }
    }
    return (unsigned char) *str2 - (unsigned char) *str1;
}
