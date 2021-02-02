#include <stdio.h>
#include <stdlib.h>

struct ListPointer
{
    int value;
    int repeats;
    struct ListPointer *left;
    struct ListPointer *right;
};

int main() {
    int numb;
    struct ListPointer *top = NULL, *begin = NULL;
    int begin_initialized = 0;
    while (scanf("%d", &numb) != EOF) {
        if (begin_initialized == 0) {
            begin_initialized = 1;
            begin = calloc(1, sizeof(*begin));
            top = begin;
            top->value = numb;
            top->repeats = 1;
            top->left = NULL;
            top->right = NULL;
            continue;
        }
        struct ListPointer *numb_ptr = top;
        while (numb_ptr != NULL) {
            if (numb_ptr->value == numb) {
                numb_ptr->repeats++;
                if (numb_ptr != top) {
                    if (numb_ptr == begin) {
                        begin = begin->right;
                    } else {
                        numb_ptr->left->right = numb_ptr->right;
                    }
                    numb_ptr->right->left = numb_ptr->left;
                    top->right = numb_ptr;
                    numb_ptr->right = NULL;
                    numb_ptr->left = top;
                    top = numb_ptr;
                }
                break;
            }
            numb_ptr = numb_ptr->left;
        }
        if (numb_ptr == NULL) {
            top->right = calloc(1, sizeof(*(top->right)));
            top->right->left = top;
            top = top->right;
            top->value = numb;
            top->repeats = 1;
            top->right = NULL;
        }
    }
    struct ListPointer *ptr = begin;
    while (ptr != NULL) {
        printf("%d %d\n", ptr->value, ptr->repeats);
        struct ListPointer *to_free = ptr;
        ptr = ptr->right;
        free(to_free);
    }
    return 0;
}
