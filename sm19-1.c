#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int counter = 0;

void sigint_hand(int signo) {
    if (counter == 4) {
        _exit(0);
    }
    printf("%d\n", counter++);
    fflush(stdout);
    return;
}

int main() {
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    struct sigaction sa;
    sa.sa_handler = sigint_hand;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while(1) {
        sigsuspend(&oldmask);
    }
    return 0;
}
