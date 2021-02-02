#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char **argv) {
    if (fork() == 0) {
        char *cmd = argv[1];
        char *name_in = argv[2];
        int fd_in = open(name_in, O_RDONLY);
        dup2(fd_in, 0);
        close(fd_in);
        char *name_out = argv[3];
        int fd_out = open(name_out, O_WRONLY | O_TRUNC | O_CREAT, 0666);
        dup2(fd_out, 1);
        close(fd_out);
        execlp(cmd, cmd, NULL);
        perror("");
        _exit(127);
    }
    wait(NULL);
    return 0;
}
