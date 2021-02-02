#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDONLY);
    struct stat st;
    fstat(fd, &st);
    double *file_ptr = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED,fd, 0);
    double average_sum = 0;
    for (int i = 0; i != st.st_size / sizeof(average_sum); ++i) {
        average_sum += file_ptr[i];
    }
    average_sum /= (st.st_size / sizeof(average_sum));
    printf("%a\n", average_sum);
    close(fd);
    return 0;
}
