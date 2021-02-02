#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int fd[2];
    pipe(fd);
    if (fork() == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[1], argv[1], NULL);
        _exit(127);
    }
    if (fork() == 0) {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[2], argv[2], NULL);
        _exit(127);
    }
    close(fd[0]);
    close(fd[1]);
    while (wait(NULL) > 0) {}
    return 0;
}
