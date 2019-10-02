#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>

int main(int argc, char **argv) {
    char path[PATH_MAX];
    snprintf(path, PATH_MAX, argv[1]);
    DIR *dir = opendir(path);
    size_t len = PATH_MAX;
    char fullpath[PATH_MAX + 1];
    if (fullpath == NULL) {
        exit(0);
    }
    unsigned long long total_sz = 0;
    strncpy(fullpath, path, len + 1);
    fullpath[len] = 0;
    size_t path_length = strlen(path);
    fullpath[path_length] = '/';
    struct dirent* de;
    struct stat st;
    uid_t user = getuid();
    while ((de = readdir(dir)) != NULL) {
        memcpy(fullpath + path_length + 1, de->d_name, strlen(de->d_name) + 1);
        if (stat(fullpath, &st) != -1) {
            if (S_ISREG(st.st_mode) && st.st_uid == user && isupper(de->d_name[0])) {
                total_sz += st.st_size;
            }
        }
    }
    closedir(dir);
    printf("%llu\n", total_sz);
}
