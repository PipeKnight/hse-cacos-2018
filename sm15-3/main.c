#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        int fd = open(argv[i], O_RDONLY);
        struct stat fileinfo;
        if (fd == -1 || fstat(fd, &fileinfo) == -1 || !S_ISREG(fileinfo.st_mode)) {
            puts("-1");
            continue;
        }
        if (fileinfo.st_size == 0) {
            puts("0");
            continue;
        }
        void *map = mmap(0, fileinfo.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        if (map == MAP_FAILED) {
            puts("-1");
            continue;
        }
        char *data = map;
        unsigned long long cnt = 0;
        for (off_t j = 0; j < fileinfo.st_size; ++j) {
            if (data[j] == '\n') {
                ++cnt;
            }
        }
        if (data[fileinfo.st_size - 1] != '\n') {
            ++cnt;
        }
        printf("%llu\n", cnt);
        munmap(map, fileinfo.st_size);
        close(fd);
    }
}
