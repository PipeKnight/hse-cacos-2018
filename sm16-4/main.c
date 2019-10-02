#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid, prev = getpid();
    int st, num;
    while (scanf("%d", &num) > 0) {
        if ((pid = fork()) < 0) {
            exit(1);
        } else if (!pid) {
            continue;
        } else {
            waitpid(pid, &st, 0);
            if (!st) {
                printf("%d\n", num);
                exit(0);
            }
            if (getpid() == prev) {
                printf("-1\n");
                exit(0);
            }
            exit(1);
        }
    }
    return 0;
}
