#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    long double x0 = strtold(argv[1], 0);
    for (int i = argc - 1; i > 0; i-=2) {
        void *handle = dlopen(argv[i - 1], RTLD_LAZY);
        if (dlerror() == NULL) {
            void *sym = dlsym(handle, argv[i]);
            x0 = ((long double (*)(long double)) sym)(x0);
            dlclose(handle);
        }
    }    
    printf("%.15Lg\n", x0);
    return 0;
}
