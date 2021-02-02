#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int mysystem(const char *cmd) {
    int pid = fork();
    if (pid == 0) {
        int start = 0, arg_size = 0;
        char **argv = NULL;
        argv = realloc(argv, sizeof(*argv));
        int argc = 0;
        int capacity = 1;
        while (cmd[start] != '\0') {
            while (isspace(cmd[start])) {
                start++;
            }
            while (cmd[start + arg_size] != '\0' && !isspace(cmd[start + arg_size])) {
                arg_size++;
            }
            if (arg_size == 0) {
                break;
            }
            if (argc + 1 == capacity) {
                argv = realloc(argv, sizeof(*argv) * ((capacity *= 2) + 1));
            }
            argv[argc++] = strndup(cmd + start, arg_size);
            start += arg_size;
            arg_size = 0;
        }
        if (argc == 0) {
            _exit(-1);
        }
        argv = realloc(argv, sizeof(*argv) * (argc + 1));
        argv[argc] = NULL;
        execvp(argv[0], argv);
        _exit(127);
    }
    if (pid < 0) {
        return -1;
    }
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
        int code = WEXITSTATUS(status);
        if (code == 127) {
            return 1;
        } else if ((int8_t) code == -1) {
            return -1;
        }
        return code;
    }
    if (WIFSIGNALED(status)) {
        return WTERMSIG(status) + 1024;
    }
    return status;
}
