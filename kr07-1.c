#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/wait.h>
#include <limits.h>

int main(int argc, char **argv) {
    int fd = open("script.c", O_WRONLY | O_TRUNC | O_CREAT, 0600);
    FILE *file = fdopen(fd, "w");
    fprintf(file, "%s", "#include <math.h>\n"
        "#include <stdio.h>\n\n"
        "int main() {\n"
        "    long double z = 0.0;\n"
        "    while (scanf(\"\%Lg\", &z) != EOF) {\n"
        "        long double res = (");
    fprintf(file, "%s%s", argv[1], ");\n"
        "        printf(\"\%.15Lg\\n\", res);\n"
        "    }\n"
        "    return 0;\n"
        "}");
    fclose(file);
    if (fork() == 0) {
        execlp("gcc", "gcc", "script.c", "-lm", "-o" "script", NULL);
        _exit(127);
    }
    wait(NULL);
    if (fork() == 0) {
        execl("script", "script", NULL);
        _exit(127);
    }
    wait(NULL);
    return 0;
}
