#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t flag = 0;

void handler(int signo) {
    if (signo == SIGUSR1) {
        flag = 0;
    } else if (signo == SIGUSR2) {
        flag = 1;
    }
}

int main() {
    struct sigaction sa_neg = {
        .sa_handler = handler,
        .sa_flags = SA_RESTART
    };
    sigemptyset(&sa_neg.sa_mask);
    sigaction(SIGUSR1, &sa_neg, NULL);

    struct sigaction sa_sqr = {
        .sa_handler = handler,
        .sa_flags = SA_RESTART
    };
    sigemptyset(&sa_sqr.sa_mask);
    sigaction(SIGUSR2, &sa_sqr, NULL);

    long long result = 0;
    int num;
    printf("%d\n", getpid());
    fflush(stdout);
    while (scanf("%d", &num) == 1) {
        result = num;
        if (!flag) {
            result = -result;
        } else {
            result *= result;
        }
        printf("%lld\n", result);
        fflush(stdout);
    }
}
