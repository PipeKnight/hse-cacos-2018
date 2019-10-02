#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int runproc(const char *str) {
    pid_t pid;
    int st;
    if ((pid = fork()) < 0) {
        return 0;
    } else if (!pid) {
        _exit(execlp(str, "", (char *) NULL));
    } else {
        waitpid(pid, &st, 0);
    }
    return WEXITSTATUS(st) == 0 && WIFEXITED(st);
}

int main(int argc, char **argv) {
    if (argc > 3) {
        exit( !((runproc(argv[1]) || runproc(argv[2])) && runproc(argv[3])) );
    }
    return 0;
}
