#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe");
        _exit(1);
    }
    int num;
    long long ans = 0;
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork");
        _exit(1);
    } else if (!pid) {
        if ((pid = fork()) < 0) {
            perror("fork");
            _exit(1);
        } else if (!pid) {
            int num;
            close(fd[1]);
            while (read(fd[0], &num, sizeof(int)) == sizeof(int)) {
                ans += num;
            }
            close(fd[0]);
            printf("%lld\n", ans);
            fflush(stdout);
            _exit(0);
        }
        close(fd[0]);
        close(fd[1]);
        waitpid(pid, NULL, 0);
        _exit(0);
    }
    while (scanf("%d", &num) == 1) {
        if (write(fd[1], &num, sizeof(int)) != sizeof(int)) {
            _exit(1);
        }
    }
    close(fd[0]);
    close(fd[1]);
}