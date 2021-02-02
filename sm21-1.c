#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <inttypes.h>
#include <stdint.h>
#include <unistd.h>

void alarm_action(int signum) {
    return;
}

int main () {
    enum
    {
        NANO = 1000000000,
        MILLI = 1000
    };
    struct sigaction sa = {};
    sa.sa_handler = &alarm_action;
    sigaction(SIGALRM, &sa, NULL);
    struct timeval cur_time;
    int64_t sec, nsec;
    scanf("%" SCNd64, &sec);
    scanf("%" SCNd64, &nsec);
    gettimeofday(&cur_time, NULL);
    int64_t diff = (sec - (int64_t) cur_time.tv_sec) * NANO
        + nsec - (int64_t) cur_time.tv_usec * MILLI;
    if (diff < 0) {
        return 0;
    }
    struct itimerval to = {};
    to.it_value.tv_sec = diff / NANO;
    to.it_value.tv_usec = (diff % NANO) / MILLI;
    setitimer(ITIMER_REAL, &to, NULL);
    pause();
    return 0;
}
