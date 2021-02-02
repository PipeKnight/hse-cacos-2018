#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int usr1_count = 0, usr2_count = 0, need_to_print = 0;

void sigusr1_hand(int signo) {
    ++usr1_count;
    need_to_print = 1;
    return;
}
void sigusr2_hand(int signo) {
    ++usr2_count;
    return;
}

void sigterm_hand(int signo) {
    _exit(0);
}

int main() {
    struct sigaction sa1, sa2, sa3;
    sa1.sa_handler = sigusr1_hand;
    sa2.sa_handler = sigusr2_hand;
    sa3.sa_handler = sigterm_hand;
    sigemptyset(&sa1.sa_mask);
    sigemptyset(&sa2.sa_mask);
    sigemptyset(&sa3.sa_mask);
    sa1.sa_flags = SA_RESTART;
    sa2.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &sa1, NULL);
    sigaction(SIGUSR2, &sa2, NULL);
    sigaction(SIGTERM, &sa3, NULL);
    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigaddset(&mask, SIGTERM);
    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        sigsuspend(&oldmask);
        if (need_to_print) {
            printf("%d\n%d\n", usr1_count - 1, usr2_count);
            fflush(stdout);
            need_to_print = 0;
        }
    }
    return 0;
}
