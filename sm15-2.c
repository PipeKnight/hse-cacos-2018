#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

int main(int argc, char **argv) {
    enum { DATA_SIZE = 4 };
    int fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC);
    int rows = atoi(argv[2]), cols = atoi(argv[3]);
    if (cols < 1 || rows < 1) {
        close(fd);
        return 0;
    }
    ftruncate(fd, DATA_SIZE * rows * cols);
    int32_t *buf = mmap(NULL, DATA_SIZE * cols * rows, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    int32_t step_i = 0, step_j = 1;
    int32_t i = 0, j = 0, left = 0, right = cols - 1, up = 0, down = rows - 1;
    for (int32_t counter = 1; counter <= rows * cols; ++counter) {
        buf[i * cols + j] = counter;
        if (j + step_j > right) {
            up++;
            step_i = 1;
            step_j = 0;
        } else if (i + step_i > down) {
            right--;
            step_i = 0;
            step_j = -1;
        } else if (j + step_j < left) {
            down--;
            step_i = -1;
            step_j = 0;
        } else if (i + step_i < up) {
            left++;
            step_i = 0;
            step_j = 1;
        }
        i += step_i;
        j += step_j;
    }
    /*
    for (int32_t i = 0; i != rows * cols; ++i) {
        printf("%" PRId32 " ", buf[i]);
        if ((i + 1) % cols == 0) {
            printf("\n");
        }
    }
    */
    close(fd);
    return 0;
}
