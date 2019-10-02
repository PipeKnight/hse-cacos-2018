#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        char *funcname = argv[1];
        void* handle = dlopen("libm.so.6", RTLD_LAZY);
        if (handle == NULL) {
            return 1;
        }
        void *func = dlsym(handle, funcname);
        if (func == NULL) {
            return 1;
        }
        double arg;
        while (scanf("%lf", &arg) == 1) {
            double res = ((double (*)(double)) func)(arg);
            printf("%.10g\n", res);
        }
        dlclose(handle);
    }
}
