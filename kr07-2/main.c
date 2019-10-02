#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc > 4) {
        pid_t pid;
        int st;
        if ((pid = fork()) < 0) {
            exit(1);
        } else if (!pid) {
            int ferr = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0660);
            int fout = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0660);
            int fin = open(argv[2], O_RDONLY, S_IRUSR | S_IRGRP);
            if (ferr < 0 || fout < 0 || fin < 0) {
                exit(42);
            }
            if (dup2(ferr, STDERR_FILENO) < 0 ||
            dup2(fout, STDOUT_FILENO) < 0 || dup2(fin, STDIN_FILENO) < 0) {
                exit(42);
            }
            int ret = execlp(argv[1], argv[1], NULL);
            close(ferr);
            close(fout);
            close(fin);
            if (ret == -1) {
                exit(42);
            }
            exit(0);
        } else {
            waitpid(pid, &st, 0);
        }
        printf("%d\n", st);
        wait(0);
    }
    return 0;
}