#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdint.h>
#include <inttypes.h>

int n;

void local_process(int32_t *numb, int i) {
    if (*numb <= n) {
        printf("%d %" PRId32 "\n", i, *numb);
        fflush(stdout);
    }
    (*numb)++;
    return;
}

void process(int fd_in, int fd_out, int32_t *numb, int i) {
    while (*numb < n) {
        read(fd_in, numb, sizeof(*numb));
        local_process(numb, i);
        write(fd_out, numb, sizeof(*numb));
    }
}

int main(int argc, char *argv[]) {
    n = atol(argv[1]);
    int fd_p2_p1[2];
    pipe(fd_p2_p1);
    int fd_p1_p3[2];
    pipe(fd_p1_p3);
    int fd_p3_p2[2];
    pipe(fd_p3_p2);
    int32_t numb = 1;
    // P2
    if (fork() == 0) {
        // P3
        if (fork() == 0) {
            local_process(&numb, 3);
            write(fd_p3_p2[1], &numb, sizeof(numb));
            process(fd_p1_p3[0], fd_p3_p2[1], &numb, 3);
        }
        process(fd_p3_p2[0], fd_p2_p1[1], &numb, 2);
        wait(NULL);
    }
    process(fd_p2_p1[0],fd_p1_p3[1] , &numb, 1);
    close(fd_p1_p3[0]); close(fd_p1_p3[1]);
    close(fd_p2_p1[0]); close(fd_p2_p1[1]);
    close(fd_p3_p2[0]); close(fd_p3_p2[1]);
    wait(NULL);
    return 0;
}
