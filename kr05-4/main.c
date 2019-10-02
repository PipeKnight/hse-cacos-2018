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
        char buffer[4];
        unsigned n;
        while (scanf("%u", &n) == 1) {
            buffer[0] = n >> (3 * OCTET);
            buffer[1] = n >> (2 * OCTET);
            buffer[2] = n >> OCTET;
            buffer[3] = n;
            write(descr, buffer, 4);
        }
        close(descr);
    }
    return 0;
}
