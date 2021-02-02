#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

volatile int32_t counter = 0;
volatile int sig = 0;

void sig_handler(int signo) {
    if (signo == SIGUSR1) {
        counter += 5;
    }
    if (signo == SIGUSR2) {
        counter -= 4;
    }
    sig = signo;
    return;
}

int main() {
    struct sigaction sa;
    sa.sa_handler = &sig_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    sigset_t oldmask;
    sigprocmask(SIG_BLOCK, &sa.sa_mask, &oldmask);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        sigsuspend(&oldmask);
        printf("%d %" PRId32 "\n", sig, counter);
        fflush(stdout);
        if (counter < 0) {
            sigprocmask(SIG_UNBLOCK, &sa.sa_mask, NULL);
            exit(0);
        }
    }
}
