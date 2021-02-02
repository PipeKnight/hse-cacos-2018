#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char const *argv[]) {
    int fd[2];
    pipe(fd);
    if (fork() == 0) {
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
        if (fork() == 0) {
            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }
        wait(NULL);
        if (fork() == 0) {
            execlp(argv[2], argv[2], NULL);
            _exit(1);
        }
        wait(NULL);
        return 0;
    }
    if (fork() == 0) {
        int fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0600);
        dup2(fd_out, 1);
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        close(fd_out);
        execlp(argv[3], argv[3], NULL);
        _exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    while (wait(NULL) > 0) {}
    return 0;
}
