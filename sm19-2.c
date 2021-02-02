#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int (*volatile process)(int);

int process_usr1(volatile int x) {
    return -x;
}

int process_usr2(volatile int x) {
    return x * x;
}

void sigusr1_hand(int signo) {
    process = &process_usr1;
    return;
}
void sigusr2_hand(int signo) {
    process = &process_usr2;
    return;
}

int main() {
    int numb = 0;
    struct sigaction sa1, sa2;
    sa1.sa_handler = sigusr1_hand;
    sa2.sa_handler = sigusr2_hand;
    sa1.sa_flags = SA_RESTART;
    sa2.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &sa1, NULL);
    sigaction(SIGUSR2, &sa2, NULL);
    process = &process_usr1;
    printf("%d\n", getpid());
    fflush(stdout);
    while (scanf("%d", &numb) != EOF) {
        printf("%d\n", process(numb));
        fflush(stdout);
    }
    return 0;
}
