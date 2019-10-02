#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

enum { BUFFERSIZE = 4096 };

void copy_file(int in_fd, int out_fd) {
    char buf[BUFFERSIZE];
    int fread;
    while((fread = read(in_fd, buf, BUFFERSIZE)) != 0) {
        if (fread == -1) {
            break;
        }
        int cnt = 0;
        while (cnt != fread) {
            cnt += write(out_fd, buf + cnt, fread - cnt);
        }
    }
}
