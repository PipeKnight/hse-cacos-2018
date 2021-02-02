#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    unsigned int n = 0;
    scanf("%u", &n);
    for (unsigned int i = 1; i <= n; ++i) {
        printf("%u", i);
        if (i == n) {
            printf("\n");
        } else {
            printf(" ");
        }
        fflush(0);
        if (fork() > 0) {
            wait(NULL);
            return 0;
        }
    }
}
