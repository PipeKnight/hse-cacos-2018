#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int procs, st;
    scanf("%d", &procs);
    for (int i = 1; i <= procs; ++i) {
        if ((pid = fork()) < 0) {
            _exit(1);
        } else if (!pid) {
            printf("%d", i);
            if (i != procs) {
                putchar(' ');
            } else {
                putchar('\n');
            }
            exit(0);
        }
        wait(0);
    }
    for (int i = 1; i <= procs; ++i) {
        wait(&st);
    }
}
