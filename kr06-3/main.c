#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

double f(double i, double j) {
    return 2 * sin(i) + 4 * cos(j / 2);
}

int main(int argc, char **argv) {
    if (argc > 3) {
        unsigned rows = strtoul(argv[2], NULL, 0);
        unsigned cols = strtoul(argv[3], NULL, 0);
        unsigned long long size = rows * cols;
        unsigned long long byte_size = size * sizeof(double);
        int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
        if (fd == -1 || ftruncate(fd, byte_size) != 0 ||
            lseek(fd, byte_size - 1, SEEK_SET) == -1 || write(fd, "", 1) == -1) {
            exit(1);
        }
        void *map = mmap(0, byte_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (map == MAP_FAILED) {
            exit(1);
        }
        double *matrix = map;
        for (unsigned i = 0; i < rows; ++i) {
            for (unsigned j = 0; j < cols; ++j) {
                matrix[cols * i + j] = f(i, j);
            }
        }
        munmap(map, byte_size);
        close(fd);
        return 0;
    }
}