#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int count1 = 0;
volatile int count2 = 0;

void handler(int signo) {
    if (signo == SIGUSR1) {
        ++count1;
    } else if (signo == SIGUSR2) {
        ++count2;
    } else if (signo == SIGTERM) {
        _exit(0);
    }
}

int main() {
    struct sigaction sa1 = {
        .sa_handler = handler,
        .sa_flags = SA_RESTART
    };
    sigemptyset(&sa1.sa_mask);
    sigaction(SIGUSR1, &sa1, NULL);

    struct sigaction sa2 = {
        .sa_handler = handler,
        .sa_flags = SA_RESTART
    };
    sigemptyset(&sa2.sa_mask);
    sigaction(SIGUSR2, &sa2, NULL);

    struct sigaction sa3 = {
        .sa_handler = handler,
        .sa_flags = SA_RESTART
    };
    sigemptyset(&sa3.sa_mask);
    sigaction(SIGTERM, &sa3, NULL);

    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigaddset(&mask, SIGTERM);

    int count1_old = 0;
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        sigprocmask(SIG_BLOCK, &mask, &oldmask);
        sigsuspend(&oldmask);
        if (count1 - count1_old) {
            printf("%d %d\n", count1 - 1, count2);
            fflush(stdout);
            count1_old = count1;
        }
        sigprocmask(SIG_UNBLOCK, &mask, &oldmask);
    }
}
