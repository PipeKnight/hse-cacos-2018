#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { SEC_IN_DAY = 24 * 60 * 60, STARTING_YEAR = 1900 };

int main(int argc, char **argv) {
    if (argc >= 2) {
        int year = strtol(argv[1], NULL, 0);
        int month = strtol(argv[2], NULL, 0);
        struct tm Time;
        struct tm* CurTime;
        time_t cur;
        Time.tm_year = year - STARTING_YEAR;
        Time.tm_mon = month - 1;
        Time.tm_mday = 1;
        Time.tm_hour = 12;
        Time.tm_min = 0;
        Time.tm_sec = 0;
        cur = mktime(&Time);
        CurTime = localtime(&cur);
        int ans = 0;
        //printf("%s%s\n", asctime(&Time), asctime(CurTime));
        //printf("%d %d\n", CurTime->tm_mon, Time.tm_mon);
        while (CurTime->tm_mon == Time.tm_mon) {
            //printf("%s\n", asctime(CurTime));
            if (1 <= CurTime->tm_wday && CurTime->tm_wday <= 4) {
                ans += 8;
            } else if (CurTime->tm_wday == 5) {
                ans += 6;
            }
            cur += SEC_IN_DAY;
            CurTime = localtime(&cur);
        }
        printf("%d\n", ans);
    }
}
