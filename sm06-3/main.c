#include <stdio.h>
#include <stdlib.h>

typedef struct BinTree
{
    int key;
    struct BinTree *left; // less
    struct BinTree *right; // more
} BinTree;

void Print(BinTree* L) {
    if (L == NULL) {
        return;
    }
    Print(L->right);
    printf("%d ", L->key);
    Print(L->left);
}

void Clear(BinTree *L) {
    if (L != NULL) {
        Clear(L->right);
        Clear(L->left);
        free(L);
    }
}

BinTree* Push(BinTree *L, int a) {
    if (L == NULL) {
        BinTree *nL = calloc(1, sizeof(struct BinTree));
        if (nL == NULL) {
            exit(228);
        }
        nL->key = a;
        nL->left = NULL;
        nL->right = NULL;
        return nL;
    }
    BinTree *t = L;
    BinTree *pr = NULL;
    while (t != NULL) {
        pr = t;
        if (t->key == a) {
            break;
        }
        else if (t->key > a) {
            t = t->left;
        }
        else if (t->key < a) {
            t = t->right;
        }
    }
    if (t == NULL) {
        BinTree *nL = calloc(1, sizeof(struct BinTree));
        if (nL == NULL) {
            Clear(L);
            exit(228);
        }
        nL->key = a;
        nL->left = NULL;
        nL->right = NULL;
        if (pr->key > a) {
            pr->left = nL;
        }
        else {
            pr->right = nL;
        }
    }
    return L;
}

int main()
{
    int a = 0;
    BinTree *MyBinTree = NULL;
    while (scanf("%d", &a) != EOF) {
        if (a != 0) {
            MyBinTree = Push(MyBinTree, a);
        }
        else {
            Print(MyBinTree);
            printf("0 ");
            BinTree *tt = MyBinTree;
            MyBinTree = NULL;
            Clear(tt);
        }
    }
    if (MyBinTree != NULL) {
        Print(MyBinTree);
        printf("0 ");
        Clear(MyBinTree);
    }
    putchar('\n');
    return 0;
}