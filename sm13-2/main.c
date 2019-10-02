#include <stdio.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    unsigned long long total_sz = 0;
    struct stat finfo;
    for (int i = 1; i < argc; ++i) {
        if (lstat(argv[i], &finfo) == 0 && S_ISREG(finfo.st_mode) && (finfo.st_nlink == 1)) {
            total_sz += finfo.st_size;
        }
    }
    printf("%llu\n", total_sz);
}
