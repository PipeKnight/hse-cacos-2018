#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main() {
    time_t today = time(NULL);
    int32_t shift_day = 0;
    while (scanf("%" PRId32, &shift_day) != EOF) {
        int64_t shift_sec = ((int64_t) shift_day) * 24 * 60 * 60;
        int64_t cur_sec = today + shift_sec;
        if ((time_t) shift_sec != shift_sec || (time_t) cur_sec != cur_sec) {
            printf("OVERFLOW\n");
        } else {
            time_t res_time = (time_t) cur_sec;
            struct tm *time_ptr = localtime(&res_time);
            int year = time_ptr->tm_year + 1900;
            int month = time_ptr->tm_mon + 1;
            int day = time_ptr->tm_mday;
            printf("%04d-%02d-%02d\n", year, month, day);
        }
    }
    return 0;
}
