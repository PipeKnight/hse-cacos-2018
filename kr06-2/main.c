#include <dlfcn.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc >= 2) {
        float x0 = strtof(argv[1], NULL);
        for (int i = 2; i < argc; i += 2) {
            char *name = argv[i];
            int j = i;
            while (strcmp(name, "-") == 0) {
                j -= 2;
                name = argv[j];
            }
            void* handle = dlopen(name, RTLD_LAZY);
            if (handle != NULL) {
                void *func = dlsym(handle, argv[i + 1]);
                if (func != NULL) {
                    x0 = ((float (*)(float))func)(x0);
                }
                dlclose(handle);
            }
        }
        printf("%.6g\n", x0);
    }
}
