#include <stdio.h>
#include <stdlib.h>

int mystrpunktcmp(const char *str1, const char *str2) {
    while((*str1 != '\x0') && (*str2 != '\x0'))
    {
        if ((*str1 == '.') || (*str1 == ',') || (*str1 == ':') ||
            (*str1 == ';') || (*str1 == '?') || (*str1 == '!')) {
            str1++;
        }
        else if ((*str2 == '.') || (*str2 == ',') || (*str2 == ':') ||
            (*str2 == ';') || (*str2 == '?') || (*str2 == '!')) {
            str2++;
        }
        else if (*str1 == *str2) {
            str1++;
            str2++;
        }
        else {
            break;
        }
    }
    while ((*str1 == '.') || (*str1 == ',') || (*str1 == ':') ||
        (*str1 == ';') || (*str1 == '?') || (*str1 == '!')) {
        str1++;
    }
    while ((*str2 == '.') || (*str2 == ',') || (*str2 == ':') ||
        (*str2 == ';') || (*str2 == '?') || (*str2 == '!')) {
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

/*int main() {
    printf("%d\n", mystrpunktcmp("a:90102abs", "a.512x"));
    printf("%d\n", mystrpunktcmp("a:abs", "a.absx"));
    printf("%d\n", mystrpunktcmp("a:abs", "a.abs"));
    printf("%d\n", mystrpunktcmp(",,.,.:;;::::????!!!!!!", "ÿ.abs"));
}*/
