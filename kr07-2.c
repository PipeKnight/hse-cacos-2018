#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
 
int main(int argc, char *argv[]) {
    int arg_beg = 1, arg_end = 1; 
    for (int i = 1; i < argc; ++i) {
        if (i == argc - 1 || strcmp(argv[i], "END") == 0) {
            if (arg_end != argc - 1) {
                argv[arg_end] = NULL;
            }
            if (fork() == 0) {
                char **newargv;
                newargv = argv + arg_beg;
                execvp(argv[arg_beg], newargv);
                _exit(1);
            }
            int status;
            wait(&status);
            if (WIFSIGNALED(status) || (WIFEXITED(status) && (WEXITSTATUS(status) != 0))) {
                return 1;
            }
            arg_beg = i + 1;
            arg_end = arg_beg;
        } else {
            arg_end++;
        }
    }
    return 0;
}
