#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>

enum { INTMIN = -2147483648 };

struct Elem
{
    struct Elem *next;
    char *str;
};

struct Elem *dup_elem(struct Elem *head) {
    struct Elem *prev = NULL;
    struct Elem *result = head;
    char *eptr;
    while (head != NULL) {
        eptr = NULL;
        errno = 0;

        long value = strtol((*head).str, &eptr, 10);
        int32_t a = value;
        if (!*(*head).str || *eptr || errno) {
            errno = 0;
        }
        else if (value != INTMIN && (long) a == value) {
            struct Elem *s = malloc(sizeof(*s));
            (*s).str = malloc(11 * sizeof(char));
            sprintf((*s).str, "%ld", value - 1);
            (*s).next = head;
            if (prev == NULL) {
                result = s;
            }
            else {
                (*prev).next = s;
            }
        }
        prev = head;
        head = (*head).next;
    }
    return result;
};

