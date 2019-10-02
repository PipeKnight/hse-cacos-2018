#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        int fd = open(argv[1], O_RDONLY);
        struct stat fileinfo;
        if (fd == -1 || fstat(fd, &fileinfo) == -1) {
            exit(0);
        }
        void *map = mmap(0, fileinfo.st_size, PROT_READ, MAP_SHARED, fd, 0);
        if (map == MAP_FAILED) {
            exit(0);
        }
        double *arr = map;
        double res = 0;
        uint64_t cnt = fileinfo.st_size / sizeof(double);
        for (off_t i = 0; i < cnt; ++i) {
            res += arr[i];
        }
        res /= cnt;
        printf("%a\n", res);
        munmap(map, fileinfo.st_size);
        close(fd);
        return 0;
    }
}