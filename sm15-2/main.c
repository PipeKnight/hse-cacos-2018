#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

enum { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3 };

int main(int argc, char **argv) {
    if (argc > 3) {
        int rows = strtoul(argv[2], NULL, 10);
        int cols = strtoul(argv[3], NULL, 10);
        int size = rows * cols;
        long long filesize = (long long)size * sizeof(int);
        int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
        if (fd == -1 || lseek(fd, filesize - 1, SEEK_SET) == -1 || write(fd, "", 1) == -1) {
            exit(0);
        }
        void *map = mmap(0, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (map == MAP_FAILED) {
            exit(0);
        }
        int *matrix = map;
        int i = 0, j = 0;
        int lborder = 0;
        int uborder = 1;
        int rborder = cols - 1;
        int dborder = rows - 1;
        char dir = RIGHT;
        for (int cur = 1; cur <= size; ++cur) {
            matrix[cols * i + j] = cur;
            if (dir == RIGHT) {
                if (j == rborder) {
                    dir = DOWN;
                    ++i;
                    --rborder;
                } else {
                    ++j;
                }
            } else if (dir == DOWN) {
                if (i == dborder) {
                    dir = LEFT;
                    --j;
                    --dborder;
                } else {
                    ++i;
                }
            } else if (dir == LEFT) {
                if (j == lborder) {
                    dir = UP;
                    --i;
                    ++lborder;
                } else {
                    --j;
                }
            } else { // dir == UP
                if (i == uborder) {
                    dir = RIGHT;
                    ++j;
                    ++uborder;
                } else {
                    --i;
                }
            }
        }
        munmap(map, filesize);
        close(fd);
        return 0;
    }
}
