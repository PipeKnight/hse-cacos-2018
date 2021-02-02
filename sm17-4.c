#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

int myrand() {
    int val = 0;
    int fd = open("/dev/urandom", O_RDONLY);
    read(fd, &val, sizeof(val));
    close(fd);
    return val;
}

char *getpath() {
    char *path = getenv("XDG_RUNTIME_DIR");
    if (path != NULL) {
        return path;
    }
    path = getenv("TMPDIR");
    if (path != NULL) {
        return path;
    }
    return "/tmp";
}

int main(int argc, char **argv) {
    srand(time(NULL));
    enum {
        DEF_NAME_LEN = 40
    };
    char path[PATH_MAX] = "";
    int fd = -1;
    unsigned int ind = 0;
    while (fd < 0) {
        snprintf(path, sizeof(path), "%s/%u.py",getpath(), (ind = myrand()));
        fd = open(path, O_RDWR | O_TRUNC | O_CREAT | O_EXCL, 0700); 
    }
    FILE *file = fdopen(fd, "w");
    char head[] = "#!/usr/bin/python3\nimport os\nprint(";
    fprintf(file, "%*s", (int) sizeof(head) - 1, head);
    for (int i = 1; i != argc; ++i) {
        if (i != 1) {
            fprintf(file, "*");
        }
        fprintf(file, "%s", argv[i]);
    }
    fprintf(file, ")\n");
    char delete_itself[] = "os.remove(os.path.abspath(__file__))";
    fprintf(file, "%s", delete_itself);
    fclose(file);
    char *newargv[] = { path, NULL };
    char *newenv[] = { NULL };
    execve(path, newargv, newenv);
    return 0;
}
