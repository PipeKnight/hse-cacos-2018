#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int my_exec(char *cmd) {
    int pid;
    if ((pid = fork()) == 0) {
        execlp(cmd, cmd, NULL);
        _exit(127);
    }
    if (pid < 0) {
        return 0;
    }
    int status;
    waitpid(pid, &status, 0);
    return (WIFEXITED(status) && (WEXITSTATUS(status) == 0));
}

int main(int argc, char *argv[]) {
    int fd[2];
    pipe(fd);
    if (fork() == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[2], argv[2], NULL);
        _exit(1);
    }
    if (fork() == 0) {
        dup2(fd[0], 0);
        int fd_file = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0660);
        dup2(fd_file, 1);
        dup2(fd_file, 2);
        close(fd_file);
        close(fd[0]);
        close(fd[1]);
        if (!(my_exec(argv[3]) || my_exec(argv[4]))) {
            return 1;
        }
    }
    close(fd[0]);
    close(fd[1]);
    while (wait(NULL) > 0) {}
    return 0;
}
