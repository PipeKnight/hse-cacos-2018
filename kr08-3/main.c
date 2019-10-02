#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/eventfd.h>

void pingpong(int pfd0, int pfd1, int num, int n) {
    int cur;
    while (read(pfd0, &cur, sizeof(int)) > 0) {
        printf("%d %d\n", num, cur); 
        fflush(stdout);
        if (cur == n) {
            _exit(0);
        }
        ++cur;
        write(pfd1, &cur, sizeof(int));
    }
    close(pfd0);
    close(pfd1);
}

int main(int argc, char **argv) {
    int n = atoi(argv[1]);
    int pfd12[2], pfd23[2], pfd13[2];
    pid_t pid;
    pipe(pfd12);
    pipe(pfd23);
    pipe(pfd13);
    if (!(pid = fork())) {
        if (!(pid = fork())) {
            close(pfd12[0]);
            close(pfd12[1]);
            close(pfd23[0]);
            close(pfd13[1]);
            int tmp = 1;
            printf("3 %d\n", tmp);
            fflush(stdout);
            if (tmp == n) {
                _exit(0);
            }
            ++tmp;
            write(pfd23[1], &tmp, sizeof(int));
            pingpong(pfd13[0], pfd23[1], 3, n);
            _exit(0);
        }
        close(pfd13[0]);
        close(pfd13[1]);
        close(pfd23[1]);
        close(pfd12[0]);
        pingpong(pfd23[0], pfd12[1], 2, n);
        _exit(0);
    }
    close(pfd23[0]);
    close(pfd23[1]);
    close(pfd12[1]);
    close(pfd13[0]);
    pingpong(pfd12[0], pfd13[1], 1, n);
    _exit(0);
}
