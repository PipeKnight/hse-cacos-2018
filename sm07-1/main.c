#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef double (*funcptr_t)(double);

typedef struct Elem
{
    const char *name;
    funcptr_t f;
} Elem;

typedef struct FunctionTable
{
    Elem *data;
    size_t size;
    size_t reserved;
} FunctionTable;

FunctionTable* CreateTable() {
    FunctionTable *T = calloc(1, sizeof(*T));
    T->size = 0;
    T->reserved = 8;
    T->data = calloc(T->reserved, sizeof(*(T->data)));
    return T;
}

void Push(FunctionTable *T, char *s, funcptr_t f) {
    if (T->size == T->reserved) {
        T->data = realloc(T->data, (T->reserved *= 2) * sizeof(*(T->data)));
    }
    T->data[T->size].name = s;
    T->data[T->size].f = f;
    T->size++;
}

int main()
{
    FunctionTable *MyTable = CreateTable();
    Push(MyTable, "sin", sin);
    Push(MyTable, "cos", cos);
    Push(MyTable, "tan", tan);
    Push(MyTable, "exp", exp);
    Push(MyTable, "log", log);
    Push(MyTable, "sqrt", sqrt);
    //printf("%f", MyTable->data[0].f(1.5));
    char fl = 1;
    while (fl) {
        char* name; //[10];
        double val;
        if (scanf("%ms %lf", &name, &val) != 2) {
            fl = 0;
        } else {
            int ind = -1;
            for (int i = 0; i < MyTable->size; ++i) {
                //printf("%s %s", name, MyTable->data[i].name);
                if (strcmp(name, MyTable->data[i].name) == 0) {
                    ind = i;
                    break;
                }
            }
            double c = NAN;
            if (ind != -1) {
                c = MyTable->data[ind].f(val);
            }
            printf("%a\n", c);
        }
        //free(name);
    }
    return 0;
}