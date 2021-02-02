#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <inttypes.h>
#include <stdint.h>

int main() {  
    int fd[2];
    pipe(fd);
    if (fork() == 0) {
        close(fd[1]);
        if (fork() == 0) {
            close(fd[1]);
            long long sum = 0;
            int32_t out;
            while (read(fd[0], &out, sizeof(out)) > 0) {
                sum += out;
            }
            printf("%lld\n", sum);
            close(fd[0]);
            return 0;
        }
        close(fd[0]);
        wait(NULL);
        return 0;   
    }
    close(fd[0]);
    int32_t in;
    while (scanf("%d", &in) != EOF) {
        write(fd[1], &in, sizeof(in));
    }
    close(fd[1]);
    wait(NULL);
    return 0;
}
