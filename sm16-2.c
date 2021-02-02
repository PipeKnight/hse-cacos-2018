#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <inttypes.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    enum {
        N_PROCESS = 3,
        N_CHR = 8,
    };
    for (int i = 0; i != N_PROCESS; ++i) {
        if (fork() == 0) {
            char buf[N_CHR + 1];
            read(0, buf, sizeof(buf) - 1);
            buf[N_CHR] = '\0';
            int32_t val = atol(buf);
            printf("%d %" PRId32 "\n", i + 1, val * val);
            return 0;
        }
    }
    while (wait(NULL) > 0) {}
    return 0;
}
