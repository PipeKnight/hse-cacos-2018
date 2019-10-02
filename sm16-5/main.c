#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc > 5) {
        size_t N = atoi(argv[1]);
        char *f = argv[2];
        int A0 = atoi(argv[3]);
        int D = atoi(argv[4]);
        int K = atoi(argv[5]);
        int fd = open(f, O_RDWR | O_CREAT | O_TRUNC, 0600);
        if (fd == -1 || close(fd) == -1) {
            exit(1);
        }
        pid_t *pids = malloc(sizeof(pid_t) * N);
        int cur, st;
        for (int i = 0; i < N; ++i) {
            if ((pids[i] = fork()) < 0) {
                exit(1);
            } else if (!pids[i]) {
                int fd = open(f, O_RDWR);
                if (fd == -1) {
                    exit(1);
                }
                cur = A0 + i * D;
                for (int j = 0; j < K * N; j += N) {
                    lseek(fd, sizeof(int) * (i + j), SEEK_SET);
                    write(fd, &cur, sizeof(int));
                    cur += N * D;
                }
                close(fd);
                exit(0);
            }
        }
        for (int i = 0; i < N; ++i) {
            waitpid(pids[i], &st, 0);
        }
        free(pids);
    }
}
