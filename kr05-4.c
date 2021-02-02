#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>


int main () {
    struct tm *tm;
    int year, month, day_of_week;
    scanf("%d%d%d", &year, &month, &day_of_week);
    time_t seconds = time(NULL);
    tm = localtime(&seconds);
    tm->tm_year = year - 1900;
    tm->tm_mon = month - 1;
    for (int i = 1; i <= 31; ++i) {
        tm->tm_mday = i;
        mktime(tm);
        if (tm->tm_mon != (month - 1)) {
            break;
        }
        if (tm->tm_wday == day_of_week) {
            printf("%d\n", tm->tm_mday);
        }
    }

    return 0;
}
