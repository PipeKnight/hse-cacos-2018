#include <stdio.h>
#include <stdlib.h>

int mystrcmp(const char *str1, const char *str2) {
    while((*str1 != '\x0') && (*str1 == *str2))
    {
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

// site with helpful hints: stackoverflow