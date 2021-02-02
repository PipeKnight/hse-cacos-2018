#include <sys/mman.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd = open(argv[1], O_RDONLY);
    struct stat st;
    fstat(fd, &st);
    if (st.st_size == 0) {
        printf("%d\n%d\n%d\n", 0, 0, 0);
        return 0;
    }
    unsigned char *buf;
    int left = 1, right = st.st_size + 1;
    while (right - left > 1) {
        unsigned int middle = (left + right) / 2;
        buf = mmap(NULL, middle, PROT_READ, MAP_SHARED, fd, 0);
        if (buf == MAP_FAILED) {
            right = middle;
        } else {
            munmap(buf, middle);
            left = middle;
        }
    }
    int page_size = left;
    int64_t sum = 0;
    int64_t cur_val = 0;
    unsigned int shift = 0;
    unsigned char high_bit_mask = (1 << (CHAR_BIT - 1));
    unsigned int fsize_pages = (st.st_size - 1) / page_size + 1;
    for (unsigned int page = 1; page <= fsize_pages; ++page) {
        buf = mmap(NULL, page_size, PROT_READ, MAP_SHARED, fd, (page - 1) * page_size);
        unsigned int cur_map;
        if (st.st_size < page_size * page) {
            cur_map = st.st_size - page_size * (page - 1);
        } else {
            cur_map = page_size;
        }
        for (unsigned int i = 0; i != cur_map; ++i) {
            unsigned char cur_byte = buf[i];
            cur_val |= (((int64_t) cur_byte & (~high_bit_mask)) << shift);
            shift += CHAR_BIT - 1;
            if ((cur_byte & high_bit_mask) == 0) {
                if (cur_byte & (high_bit_mask >> 1)) {
                    cur_val |= ((~((int64_t) 0)) << shift);
                }
                // printf("%" PRId64 "\n", cur_val);
                sum += cur_val;
                shift = 0;
                cur_val = 0;
            }
        }
        munmap(buf, page_size);
    }
    close(fd);
    printf("%llu\n%u\n%" PRId64 "\n", st.st_size, page_size, sum);
    return 0;
}






