#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

enum { PROCS = 3, LENGTH = 8 };

int main() {
    pid_t pid;
    int st = 0;
    for (int i = 1; i <= PROCS; ++i) {
        if ((pid = fork()) < 0) {
            _exit(1);
        } else if (!pid) {
            char data[LENGTH];
            int k;
            if (read(0, &data, LENGTH) < LENGTH) {
                exit(1);
            }
            k = atoi(data);
            k *= k;
            printf("%d %d\n", i, k);
            fflush(stdout);
            exit(0);
        }
    }
    for (int i = 0; i < PROCS; ++i) {
        wait(&st);
    }
}
