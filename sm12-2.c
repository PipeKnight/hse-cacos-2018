#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void copy_file(int in_fd, int out_fd) {
    enum { LCL_BUF_SZ = 4096 };
    unsigned char buf[LCL_BUF_SZ];
    ssize_t was_read = 0;
    while ((was_read = read(in_fd, buf, sizeof(buf))) > 0) {
        ssize_t shift = 0;
        while (1) {
            ssize_t was_wrote = write(out_fd, buf + shift, was_read);
            if (was_wrote <= 0) {
                break;
            }
            shift += was_wrote;
            was_read -= was_wrote;
        }
    }
}
