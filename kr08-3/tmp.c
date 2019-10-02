#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/eventfd.h>

int main(int argc, char **argv) {
    double x0 = strtod(argv[1], NULL);
    int n = atoi(argv[2]);
    double dx = strtod(argv[3], NULL);
    int pfd_sin[2], pfd_cos[2];
    pid_t pid;
    pipe(pfd_sin);
    pipe(pfd_cos);
    double x1 = x0;
    double x2 = x0;
    if (!(pid = fork())) {
        if (!(pid = fork())) {
            for (int i = 0; i < n; ++i) {
                close(pfd_sin[0]);
                write(pfd_sin[1], sin(x1), sizeof(double));
                close(pfd_sin);
                x1 += dx;
            }
        }
        close(pfd_cos[0]);
        write(pfd_cos[1], sin(x1), sizeof(double));
        close(pfd_cos);
        x1 += dx;
    }
    for (int i = 0; i < n; ++i) {
        double x = left + i * dx;
        double res = ((double (*)(double))func)(x) * dx;
        result += res;
    }
    printf("%.10g\n", result);
}
