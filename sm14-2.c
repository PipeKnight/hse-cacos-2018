#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    double arg = 0, res = 0;
    void *handle = dlopen("/lib/libm.so.6", RTLD_LAZY);
    void *func = dlsym(handle, argv[1]);
    while (scanf("%lf", &arg) == 1) {
        res = ((double (*)(double)) func)(arg);
        printf("%.10g\n", res);
    }
    dlclose(handle);
    return 0;
}
