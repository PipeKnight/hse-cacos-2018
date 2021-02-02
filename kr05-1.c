#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

int main(int argc, char **argv) { 
    long long sz = 0;
    int low = atoi(argv[2]);
    int high = atoi(argv[3]);
    for (int i = low; i <= high; ++i) {
        char name[PATH_MAX];
        snprintf(name, sizeof(name), argv[1], i);
        struct stat st;
        if (lstat(name, &st) >= 0
            && S_ISREG(st.st_mode)
            && getuid() == st.st_uid) {
            sz += st.st_size;
        }
    }
    printf("%lld\n", sz);
}
