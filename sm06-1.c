#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct ListPointer
{
    int value;
    struct ListPointer *left;
};

int main() {
    int numb;
    struct ListPointer *last = NULL, *cur_ptr = NULL;
    while (scanf("%d", &numb) != EOF) {
        cur_ptr = calloc(1, sizeof(*cur_ptr));
        cur_ptr->value = numb;
        cur_ptr->left = last;
        last = cur_ptr;
    }
    while (cur_ptr != NULL) {
        printf("%d\n", cur_ptr->value);
        struct ListPointer *temp = cur_ptr->left;
        free(cur_ptr);
        cur_ptr = temp;
    }
    return 0;
}
