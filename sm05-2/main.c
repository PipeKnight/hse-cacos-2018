#include <stdio.h>
#include <stdlib.h>

enum { WORD = 0, SLASH = 1 };

void normalize_path(char *buf) {
    char *read = buf;
    char *write = buf;
    int STATE = WORD;
    while (*read != '\x0') {
        if (STATE == SLASH) {
            if (*read != '/') {
                STATE = WORD;
            }
        }
        if (STATE == WORD) {
            if (*read == '/') {
                STATE = SLASH;
            }
            *write = *read;
            ++write;
        }
        ++read;
    }
    *write = *read;
}
