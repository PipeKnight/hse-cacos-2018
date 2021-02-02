#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void *myopen(char *name, struct stat *st) {
    int fd = open(name, O_RDONLY);
    if (fd == -1) {
        return MAP_FAILED;
    }
    if (fstat(fd, st) == -1) {
        close(fd);
        return MAP_FAILED;
    }
    if (st->st_size == 0) {
        close(fd);
        return NULL;
    }
    char *buf = mmap(NULL, st->st_size, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    if (buf == NULL) {
        return MAP_FAILED;
    }
    return buf;
}

unsigned long long process_file(char *buf, struct stat st) {
    unsigned long long line_counter = 0;
    for (int j = 0; j != st.st_size; ++j) {
        if (buf[j] == '\n') {
            ++line_counter;
        }
    }
    if (buf[st.st_size - 1] != '\n') {
        ++line_counter;
    }
    return line_counter;
}

int main(int argc, char **argv) {
    for (int i = 1; i != argc; ++i) {
        struct stat st;
        char *buf = myopen(argv[i], &st);
        int succes = 1;
        if (st.st_size == 0) {
            succes = 0;
        } else if (buf == MAP_FAILED) {
            succes = -1;
        }
        if (succes == 1) {
            printf("%llu\n", process_file(buf, st));
        } else {
            printf("%d", succes);
        }
    }
    return 0;
}
