#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum { MAXSIG = 4 };

volatile int count = 0;

void sigint_handler(int signo) {
    printf("%d\n", count);
    fflush(stdout);
    if (++count == MAXSIG) {
        _exit(0);
    }
}

int main() {
    struct sigaction sa = {
        .sa_handler = sigint_handler,
        .sa_flags = SA_RESTART
    };
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) { 
        pause();
    }
}
