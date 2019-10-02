#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC,
    S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IXOTH);
    dprintf(fd, "%s", "#!/usr/bin/python3\n");
    dprintf(fd, "%s", "n = int(input())\n");
    dprintf(fd, "%s", "s = n * (n + 1) // 2\n");
    dprintf(fd, "%s", "print(s %");
    dprintf(fd, "%s", argv[2]);
    dprintf(fd, "%s", ")\n");
    close(fd);
    return 0;
}
