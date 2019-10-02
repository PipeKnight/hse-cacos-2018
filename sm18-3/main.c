#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum { STDIN = 0, STDOUT = 1 };

int main(int argc, char **argv) {
    if (argc > 4) {
        int fd[2];
        if (pipe(fd) < 0) {
            _exit(1);
        }
        pid_t pid;
        if ((pid = fork()) < 0) {
            _exit(1);
        } else if (!pid) {
            close(fd[0]);
            if (!fork()) {
                dup2(fd[1], STDOUT);
                close(fd[0]);
                close(fd[1]);
                execlp(argv[1], argv[1], NULL);
                _exit(0);
            }   
            waitpid(-1, NULL, 0);
            if (!fork()) {
                dup2(fd[1], STDOUT);
                close(fd[0]);
                close(fd[1]);
                execlp(argv[2], argv[2], NULL);
                _exit(0);
            }
            close(fd[1]);
            waitpid(-1, NULL, 0);
            _exit(0);
        }
        if ((pid = fork()) < 0) {
            _exit(1);
        } else if (!pid) {
            dup2(fd[0], STDIN);
            int filedes = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0600);
            dup2(filedes, STDOUT);
            close(fd[0]);
            close(fd[1]);
            close(filedes);
            execlp(argv[3], argv[3], NULL);
            _exit(0);
        }
        close(fd[0]);
        close(fd[1]);
        waitpid(-1, NULL, 0);
        waitpid(-1, NULL, 0);
    }
}