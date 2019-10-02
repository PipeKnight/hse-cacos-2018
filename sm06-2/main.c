#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    int key;
    int val;
    struct List *prev;
    struct List *next;
} List;

void Print(List* L) {
    if (L == NULL) {
        return;
    }
    Print(L->next);
    printf("%d %d\n", L->key, L->val);
}

void Clear(List *L) {
    while (L != NULL) {
        List *tmp = L->next;
        free(L);
        L = tmp;
    }
}

List* Push(List *L, int a) {
    if (L == NULL) {
        List *nL = calloc(1, sizeof(struct List));
        if (nL == NULL) {
            exit(228);
        }
        nL->key = a;
        nL->val = 1;
        nL->prev = NULL;
        nL->next = NULL;
        return nL;
    }
    if (L->key == a) {
        L->val++;
        return L;
    }
    List *t = L;
    while (t != NULL) {
        if (t->key == a) {
            break;
        }
        t = t->next;
    }
    if (t == NULL) {
        List *nL = calloc(1, sizeof(struct List));
        if (nL == NULL) {
            Clear(L);
            exit(228);
        }
        nL->key = a;
        nL->val = 1;
        nL->prev = NULL;
        nL->next = L;
        L->prev = nL;
        return nL;
    }
    else {
        t->val++;
        t->prev->next = t->next;
        if (t->next != NULL) {
            t->next->prev = t->prev;
        }
        t->prev = NULL;
        t->next = L;
        L->prev = t;
        return t;
    }
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