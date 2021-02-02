#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int status;
    if (fork() > 0) {
        wait(&status);
        printf("%d\n", 1);
    } else {
        if (fork() > 0) {
            wait(&status);
            printf("%d ", 2);
        } else {
            printf("%d ", 3);
        }
    }
    return 0;
}
