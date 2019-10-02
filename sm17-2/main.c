#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int mysys(const char *str) {
    pid_t pid;
    int st;
    if ((pid = fork()) < 0) {
        _exit(-1);
    } else if (!pid) {
        int ex = execl("/bin/sh", "sh", "-c", str, NULL);
        if (ex == -1) {
            _exit(127);
        } else {
            _exit(ex);
        }
    } else {
        waitpid(pid, &st, 0);
    }
    
    if (WIFSIGNALED(st)) {
        return (128 + WTERMSIG(st));
    }
    return WEXITSTATUS(st);
}
