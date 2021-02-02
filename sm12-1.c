#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char **argv) {
    int file = open(argv[1], O_WRONLY | O_TRUNC |O_CREAT, 0600);
    unsigned short cur_numb = 0;
    unsigned char buf[sizeof(cur_numb)];
    while (scanf("%hu", &cur_numb) != EOF) {
        buf[0] = cur_numb >> CHAR_BIT;
        buf[1] = cur_numb;
        write(file, buf, sizeof(buf));
    }
    close(file);
    return 0;
}
