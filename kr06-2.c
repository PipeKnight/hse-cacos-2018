#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int cols = atoi(argv[2]), rows = atoi(argv[3]);
    int fd = open(argv[1], O_RDWR | O_TRUNC | O_CREAT, 0600);
    if (fd == -1 || ftruncate(fd, rows * cols * sizeof(double)) == -1) {
        close(fd);
        return 1;
    };
    double *buf = mmap(NULL, rows * cols * sizeof(*buf), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (buf == MAP_FAILED) {
        close(fd);
        return 1;
    }
    for (int i = 0; i != rows; ++i) {
        for (int j = 0; j != cols; ++j) {
            buf[i * cols + j] = 2 * sin(((double) i) / 3) + 3 * cos((double) j);
        }
    }
    close(fd);
    return 0;
}
