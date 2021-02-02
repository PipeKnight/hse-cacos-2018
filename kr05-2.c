#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>

int main(int argc, char **argv) {
    char *name = argv[1];
    int fd = open(name, O_RDONLY);
    enum { LOCAL_SZ = 3 };
    unsigned char buf[LOCAL_SZ];
    uint32_t val = 0;
    long long sum = 0;
    while (read(fd, buf, sizeof(buf)) == LOCAL_SZ) {
        for (int i = 0; i != LOCAL_SZ; ++i) {
            val |= buf[i];
            val <<= CHAR_BIT;
        }
        int32_t res_val = val;
        res_val >>= CHAR_BIT;
        sum -= res_val;
    }
    printf("%lld\n", sum);
    return 0;
}
