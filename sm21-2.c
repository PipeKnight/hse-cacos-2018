#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/time.h>

volatile int counter = 0;
volatile uint32_t cur_prime = 0;

void alarm_action(int signum) {
    ++counter;
    printf("%" PRIu32 "\n", cur_prime);
    fflush(stdout);
    return;
}

int main() {
    enum
    {
        VIRT_USEC = 100000,
        MAX_VIRT_SEC = 8
    };
    struct sigaction sa = {};
    sa.sa_handler = &alarm_action;
    sigaction(SIGVTALRM, &sa, NULL);
    uint32_t low, high;
    scanf("%" SCNu32 "%" SCNu32, &low, &high);
    struct itimerval timer = {};
    timer.it_value.tv_usec = VIRT_USEC;
    timer.it_interval.tv_usec = VIRT_USEC;
    setitimer(ITIMER_VIRTUAL, &timer, NULL);
    for (uint32_t numb = low; numb < high; ++numb) {
        int is_prime = 1;
        for (uint32_t i = 2; (uint64_t) i * i < (uint64_t) numb; ++i) {
            if (numb % i == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            cur_prime = numb;
        }
        if (counter == MAX_VIRT_SEC) {
            return 0;
        }
    }
    if (counter < MAX_VIRT_SEC) {
        printf("%d\n", -1);
    }
    return 0;
}
