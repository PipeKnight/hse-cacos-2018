#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int status_cmd(char *cmd) {
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

int main(int argc, char **argv) {
    return !((status_cmd(argv[1]) || status_cmd(argv[2])) && status_cmd(argv[3]));
}
