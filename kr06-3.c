#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int cmp (const void *a, const void *b) {
    const double *da = (const double *) a;
    const double *db = (const double *) b;

    return (*da > *db) - (*da < *db);
}


int main(int argc, char **argv) {
    enum
    {
        PERCENTAGE_LEFT = 10,
        PERCENTAGE_RIGHT = 10
    };
    int fd = open(argv[1], O_RDONLY);
    struct stat st;
    stat(argv[1], &st);
    double *buf = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    int size = st.st_size / sizeof(*buf);
    int start = size / PERCENTAGE_LEFT;
    int end = size - size / PERCENTAGE_RIGHT;
    qsort(buf + start, end - start, sizeof(*buf), &cmp);
    size = end - start;
    start += size / PERCENTAGE_LEFT;
    end -= size / PERCENTAGE_RIGHT;
    double av_sum = 0;
    for (int i = start; i < end; ++i) {
        av_sum += buf[i];
    }
    av_sum /= end - start;
    printf("%.10g\n", av_sum);
    return 0;
}
