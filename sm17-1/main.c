#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc > 3) {
        pid_t pid;
        int st;
        if ((pid = fork()) < 0) {
            exit(1);
        } else if (!pid) {
            int fout = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
            dup2(fout, 1);
            int fin = open(argv[2], O_RDONLY, S_IRUSR | S_IWUSR);
            dup2(fin, 0);
            execlp(argv[1],argv[1], NULL);
            close(fout);
            close(fin);
            exit(0);
        } else {
            waitpid(pid, &st, 0);
        }
        wait(0);
    }
    return 0;
}