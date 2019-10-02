#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

enum { OCTET = 8 };

int main(int argc, char *argv[]) {
    char *fname = argv[1];
    int oflag = O_WRONLY | O_CREAT | O_TRUNC;
    mode_t md = S_IRUSR | S_IWUSR;
    int descr = open(fname, oflag, md);
    if (descr != -1) {
        char buffer[2];
        unsigned short n;
        while (scanf("%hu", &n) == 1) {
            buffer[0] = n >> OCTET;
            buffer[1] = n;
            write(descr, buffer, 2);
        }
        close(descr);
    }
    return 0;
}
