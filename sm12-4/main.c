#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define sizeNd sizeof(struct Node)

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

void shift(int fd, int index) {
    if (index == 0) {
        return;
    }
    struct Node result;
    if (lseek(fd, sizeNd * index, SEEK_SET) < 0) {
        exit(1);
    }
    if (read(fd, &result, sizeNd) < sizeNd) {
        exit(1);
    }
    int32_t key = result.key;
    int32_t left = result.left_idx;
    int32_t right = result.right_idx;
    shift(fd, right);
    printf("%d\n", key);
    shift(fd, left);
}

int main(int argc, char **argv) {
    char *fname = argv[1];
    int fd = open(fname, O_RDONLY);
    struct Node result;
    if (read(fd, &result, sizeNd) < sizeNd) {
        exit(0);
    }
    int32_t key = result.key;
    int32_t left = result.left_idx;
    int32_t right = result.right_idx;
    shift(fd, right);
    printf("%d\n", key);
    shift(fd, left);
}
