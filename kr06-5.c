#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    unsigned long long sum_size = 0, max_sum = strtoull(argv[2], NULL, 10);
    DIR *dirp;
    if ((dirp = opendir(argv[1])) == NULL) {
        return 0;
    }
    struct dirent *d_info;
    char *min_name = NULL;
    long max_size = 0;
    while ((d_info = readdir(dirp)) != NULL) {
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", argv[1], d_info->d_name);
        struct stat st;
        if (lstat(full_path, &st) >= 0 
                && S_ISREG(st.st_mode)) {
            sum_size += st.st_size;
            if (st.st_size > max_size) { 
                max_size = st.st_size;
                min_name = strdup(d_info->d_name);
            }
        }
    }
    if (sum_size > max_sum) {
        printf("%s\n", min_name);
    }
    closedir(dirp);
    return 0;
}
