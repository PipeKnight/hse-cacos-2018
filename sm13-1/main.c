#include <stdio.h>
#include <time.h>
#include <errno.h>

enum { SEC_IN_DAY = 24 * 60 * 60, STARTING_YEAR = 1900 };
enum { YEAR_LENGTH = 4, MON_LENGTH = 2, MDAY_LENGTH = 2 };

int main() {
    int days;
    time_t curtime, secs, ans;
    struct tm *Time;
    if ((curtime = time(NULL)) != -1) {
        while (scanf("%d", &days) == 1) {
            secs = 0;
            ans = 0;
            if (__builtin_mul_overflow(SEC_IN_DAY, days, &secs) || __builtin_add_overflow(secs, curtime, &ans)) {
                printf("OVERFLOW\n");
                continue;
            }
            Time = localtime(&ans);
            if (errno != 0 || Time == NULL) {
                printf("OVERFLOW\n");
                continue;
            }
            Time->tm_year += STARTING_YEAR;
            Time->tm_mon  += 1;
            printf("%04d-%02d-%02d\n", Time->tm_year, Time->tm_mon, Time->tm_mday);
        }
    }
    return 0;
}
