#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum { STDIN = 0, STDOUT = 1 };

int main(int argc, char **argv) {
    if (argc > 2) {
        int fd[2];
        if (pipe(fd) < 0) {
            perror("pipe");
            _exit(1);
        }
        pid_t pid1, pid2;
        if ((pid1 = fork()) < 0) {
            perror("fork");
            _exit(1);
        } else if (!pid1) {
            dup2(fd[1], STDOUT);
            close(fd[0]);
            close(fd[1]);
            execlp(argv[1], argv[1], NULL);
            perror("execlp");
            _exit(1);
        }
        close(fd[1]);
        if ((pid2 = fork()) < 0) {
            perror("fork");
            _exit(1);
        } else if (!pid2) {
            dup2(fd[0], STDIN);
            close(fd[0]);
            execlp(argv[2], argv[2], NULL);
            perror("execlp");
            _exit(1);
        }
        close(fd[0]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
    }
}
