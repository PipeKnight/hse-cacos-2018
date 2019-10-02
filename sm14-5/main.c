#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { ARG_SIZE_MAX = 64 };

typedef struct Bytes 
{
    unsigned char bytes[ARG_SIZE_MAX];
} Bytes;

void write_data(Bytes *args, int argc, char **argv, char *signature) {
    int argsize = 0;
    int itmp;
    double dtmp;
    for (int i = 4; i < argc; ++i) {
        switch(signature[i - 3]) {
        case 'i':
            itmp = atoi(argv[i]);
            memcpy(args->bytes + argsize, &itmp, sizeof(int));
            argsize += sizeof(int);
            break;
        case 'd':
            dtmp = strtod(argv[i], NULL);
            memcpy(args->bytes + argsize, &dtmp, sizeof(double));
            argsize += sizeof(double);
            break;
        case 's':
            memcpy(args->bytes + argsize, argv + i, sizeof(char*));
            argsize += sizeof(char*);
            break;
        default:
            break;
        }
    }
}


int main(int argc, char **argv) {
    if (argc >= 3) {
        char *lname = argv[1];
        char *fname = argv[2];
        char *signature = argv[3];
        void* handle = dlopen(lname, RTLD_LAZY);
        if (handle == NULL) {
            exit(0);
        }
        void *func = dlsym(handle, fname);
        if (func == NULL) {
            exit(0);
        }
        Bytes args;
        write_data(&args, argc, argv, signature);
        switch(signature[0]) {
        case 'i':
            printf("%d\n", ((int (*)(Bytes))func)(args));
            break;
        case 'd':
            printf("%.10g\n", ((double (*)(Bytes))func)(args));
            break;
        case 's':
            printf("%s\n", ((char *(*)(Bytes))func)(args));
            break;
        default:
            ((void (*)(Bytes))func)(args);
            break;
        }
        dlclose(handle);
    }
}
