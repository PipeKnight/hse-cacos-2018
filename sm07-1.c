#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef double (*funcptr_t)(double);

struct FunctionTable {
    const char *name;
    const funcptr_t fptr;
};

int main() {
    const static struct FunctionTable ftable[] =
    {
        {"sin", sin},
        {"cos", cos},
        {"exp", exp},
        {"log", log},
        {"tan", tan},
        {"sqrt", sqrt}
    };
    char *fname;
    double arg;
    while (scanf("%ms%lf", &fname, &arg) != EOF) {
        int len = sizeof(ftable) / sizeof(struct FunctionTable);
        int found = 0;
        for (int i = 0; i < len; ++i) {
            if (strcmp(ftable[i].name, fname) == 0) {
                printf("%a\n", ftable[i].fptr(arg));
                found = 1;
                break;
            }
        }
        if (found == 0) {
            printf("nan\n");
        }
    }
    free(fname);
    return 0;
}
