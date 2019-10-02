#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    int val;
    struct List *prev;
} List;

void Print(List* L) {
    if (L == NULL) {
        return;
    }
    printf("%d\n", L->val);
    Print(L->prev);
}

void Clear(List *L) {
    while (L != NULL) {
        List *tmp = L->prev;
        free(L);
        L = tmp;
    }
}

List* Push(List *L, int a) {
    List *nL = calloc(1, sizeof(struct List));
    if (nL == NULL) {
        Clear(L);
        exit(228);
    }
    nL->prev = L;
    nL->val = a;
    return nL;
}

int main()
{
    List* MyList = NULL;
    int a = 0;
    while (scanf("%d", &a) != EOF) {
        MyList = Push(MyList, a);
    }
    Print(MyList);
    Clear(MyList);
    return 0;
}