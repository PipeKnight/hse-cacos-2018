#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

int main(int argc, char **argv) {
    DIR *d = opendir(argv[1]);
    unsigned long long size = 0;
    if (d == NULL) {
        printf("%llu\n", size);
        return 0;
    }
    struct dirent *dirp;
    while ((dirp = readdir(d)) != NULL) {
        char path_name[PATH_MAX];
        snprintf(path_name, sizeof(path_name), "%s/%s", argv[1], dirp->d_name);
        struct stat st;
        int success = stat(path_name, &st);
        if (success >= 0
            && S_ISREG(st.st_mode)
            && getuid() == st.st_uid
            && isupper(dirp->d_name[0])
            ) {
            size += st.st_size;
        }
    }
    printf("%llu\n", size);
    closedir(d);
    return 0;
}
