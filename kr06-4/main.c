#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int cmp(const void* a, const void *b) {
    double A = *(double*)a;
    double B = *(double*)b;
    if (A == B) {
        return 0;
    }
    if (A < B) {
        return -1;
    }
    return 1;
}

int main(int argc, char **argv) {
    if (argc > 1) {
        struct stat finfo;
        int fd = open(argv[1], O_RDONLY);
        if (fd == -1 || fstat(fd, &finfo) == -1) {
            exit(1);
        }
        void *map = mmap(0, finfo.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
        if (map == MAP_FAILED) {
            exit(1);
        }
        double *array = (double*)map;
        int n = finfo.st_size / sizeof(double);
        int new_st = n / 10;
        int len = n - 2 * (n / 10);
        qsort(array + new_st, len, sizeof(double), cmp);
        new_st += len / 10;
        len -= 2 * (len / 10);
        double avg = 0;
        for (int i = 0; i < len; ++i) {
            avg += array[new_st + i];
        }
        avg /= len;
        printf("%.10g\n", avg);
        munmap(map, finfo.st_size);
    }
}
