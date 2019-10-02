#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc > 2) {
        char *path = argv[1];
        uint64_t SIZE_LIM = strtoull(argv[2], NULL, 10);
        size_t len = PATH_MAX + 1;
        DIR *dir = opendir(path);
        char *fullpath = malloc(len);
        if (dir == NULL || fullpath == NULL) {
            exit(0);
        }
        strncpy(fullpath, path, len);
        size_t path_length = strlen(path);
        fullpath[path_length] = '/';
        uint64_t sum_size = 0;
        struct dirent* di;
        struct stat st;
        char name[128];
        uint64_t max_size = 0;
        while ((di = readdir(dir)) != NULL) {
            memcpy(fullpath + path_length + 1, di->d_name, strlen(di->d_name) + 1);
            if (lstat(fullpath, &st) != -1 && S_ISREG(st.st_mode) && !S_ISLNK(st.st_mode)) {
                sum_size += st.st_size;
                if (max_size < st.st_size) {
                    max_size = st.st_size;
                    strcpy(name, di->d_name);
                } else if (max_size == st.st_size && strcmp(name, di->d_name) > 0) {
                    strcpy(name, di->d_name);
                }
            }
        }
        if (sum_size > SIZE_LIM) {
            puts(name);
        }
        free(fullpath);
        closedir(dir);
    }
}
