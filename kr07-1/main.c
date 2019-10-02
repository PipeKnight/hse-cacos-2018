#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int proc(void)
{
    int pid = 0;
    if (!pid) {
        printf("1\n");
    }
    return pid;
}

int main()
{
    if (printf("%d\n", (proc() == 0)) && printf("%d\n", (proc() == 0)) && printf("%d\n", (proc() == 0)) && printf("1\n")) {
        printf("OK!");
    } else {
        printf("ERROR!");
    }
    printf("Hello world!\n");
    return 0;
}
