#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
    int val = 0;
    pid_t father = getpid();
    if (scanf("%d", &val) == EOF) {
        return 0;
    }
    pid_t pid;
    while ((pid = fork()) == 0) {
        if (scanf("%d", &val) == EOF) {
            return 0;
        }
    }
    if (pid == -1) {
        return 1;
    }
    int status;
    wait(&status);
    if (!WIFEXITED(status) || WEXITSTATUS(status) == 1) {
        if (father != getpid()) {
            return 1;
        }
        val = -1;
    }
    printf("%d\n", val);
    return 0;
}
