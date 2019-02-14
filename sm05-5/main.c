#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

char *getline2(FILE *f) {
    if (f == NULL) {
        return NULL;
    }
    char *data = NULL;
    char *tmp = NULL;
    int c = 0;
    size_t size = 0;
    size_t reserved = 1;
    data = calloc(reserved, sizeof(*data));
    while (c != (int) '\n') {
        c = fgetc(f);
        if (c == EOF) {
            if (size != 0) {
                break;
            }
            free(data);
            return NULL;
        }
        if (size == reserved) {
            errno = 0;
            tmp = realloc(data, (reserved *= 2) * sizeof(*data));
            if (errno != 0) {
                free(data);
                return NULL;
            }
            data = tmp;
        }
        data[size++] = c;
    }
    if (size == reserved) {
        errno = 0;
        tmp = realloc(data, (reserved += 1) * sizeof(*data));
        if (errno != 0) {
            free(data);
            return NULL;
        }
        data = tmp;
    }
    data[size++] = 0;
    return data;
}