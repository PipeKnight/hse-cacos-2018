#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

int main(int argc, char *argv[]) {
    double aver_d = 0;
    int count_d = 0;
    int64_t sum_i = 0, str_len = 0;
    for (int i = 1; i != argc; ++i) {
        if (*argv[i] == 'i') {
            sum_i += (int64_t) strtol(argv[i] + 1, NULL, 10);
        } else if (*argv[i] == 'd') {
            aver_d += strtod(argv[i] + 1, NULL);
            count_d++;
        } else {
            int len = 0;
            while (*argv[i] != '\0') {
                len++;
                argv[i]++;
            }
            str_len += len;
        }
    }
    if (count_d != 0) {
        aver_d /= count_d;
    }
    printf("%.10g\n%" PRId64 "\n%" PRId64 "\n", aver_d, sum_i, str_len);
    return 0;
}
