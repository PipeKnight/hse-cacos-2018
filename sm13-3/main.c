#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum { STARTING_YEAR = 1900, BUFFERSIZE = 1000 };

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *fin;
        char *fname = argv[1];
        if ((fin = fopen(fname, "r")) == NULL) {
            exit(0);
        }
        char buf[BUFFERSIZE];
        struct tm Time;
        time_t cur, prev;
        int year, month;
        sscanf(buf, "%04d/%02d/%02d %02d:%02d:%02d", &year, &month,
        &(Time.tm_mday), &(Time.tm_hour), &(Time.tm_min), &(Time.tm_sec));
        Time.tm_year = year - STARTING_YEAR;
        Time.tm_mon = month - 1;
        Time.tm_isdst = -1;
        prev = mktime(&Time);
        while (fgets(buf, BUFFERSIZE, fin) != NULL) {
            if (sscanf(buf, "%04d/%02d/%02d %02d:%02d:%02d", &year, &month,
            &(Time.tm_mday), &(Time.tm_hour), &(Time.tm_min), &(Time.tm_sec)) == 6) {
                Time.tm_year = year - STARTING_YEAR;
                Time.tm_mon = month - 1;
                Time.tm_isdst = -1;
                cur = mktime(&Time);
                printf("%ld\n", cur - prev);
                prev = cur;
            }
        }
        fclose(fin);
    }
}