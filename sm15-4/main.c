#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc > 1) {
        int fd = open(argv[1], O_RDONLY);
        struct stat fileinfo;
        if (fd == -1 || fstat(fd, &fileinfo) == -1 || fileinfo.st_size == 0) {
            exit(0);
        }
    
        long long sum = 0;
        size_t sz = fileinfo.st_size;
        size_t l = 0;
        size_t r = sz + 1;
        while (r - l > 1) {
            size_t m = (r + l) / 2;
            void *map = mmap(0, m, PROT_READ, MAP_PRIVATE, fd, 0);
            if (map == MAP_FAILED) {
                r = m;
            } else {
                l = m;
            }
        }
        size_t mx = l;
        size_t cur = 0;
        while (cur < sz) {
            if (sz - cur < l) {
                l = sz - cur;
            }
            void *map = mmap(0, l, PROT_READ, MAP_PRIVATE, fd, cur);
            cur += l;
            char *data = map;
            int cnt = 0;
            while (cnt < l) {
                int res = 0;
                int more = 1;
                int shift = 0;
                int val = 0;
                while (more) {
                    val = (*data) & 0x7f;
                    res = res | (val << shift);
                    shift += 7;
                    ++cnt;
                    more = ((*data++) & 0x80) >> 7;
                }
                sum += res;
            }
        }
        printf("%d\n%d\n%lld\n", sz, mx, sum);
        close(fd);
    }
}
