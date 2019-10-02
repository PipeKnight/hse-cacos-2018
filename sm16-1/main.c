#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int st;
    if ((pid = fork()) < 0) {
        _exit(1);
    } else if (!pid) {
        if ((pid = fork()) < 0) {
            _exit(1);
        } else if (!pid) {
            printf("3 ");
            fflush(stdout);
        } else {
            waitpid(pid, &st, 0);
            printf("2 ");
            fflush(stdout);
        }
        _exit(0);
    } else {
        waitpid(pid, &st, 0);
        printf("1\n");
        fflush(stdout);
    }
}
