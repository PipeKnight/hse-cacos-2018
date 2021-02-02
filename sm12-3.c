#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

struct FileContent read_file(int fd) {
    enum { LCL_BUF_SZ = 4096 };
    char buf[LCL_BUF_SZ];
    struct FileContent fdata;
    fdata.size = 0;
    fdata.data = malloc(1);
    int was_read = 0;
    fdata.data[fdata.size] = '\0';
    while (1) {
        was_read = read(fd, buf, sizeof(buf));
        if (was_read == 0) {
            break;
        }
        if (was_read == -1) {
            free(fdata.data);
            fdata.data = NULL;
            fdata.size = -1;
            break;
        }
        int to_realloc = was_read;
        if (was_read < fdata.size) {
            to_realloc = fdata.size;
        }
        char *temp_ptr = realloc(fdata.data, fdata.size + to_realloc + 1);
        if (temp_ptr == NULL) {
            free(fdata.data);
            fdata.size = -1;
            fdata.data = NULL;
            break;
        }
        fdata.data = temp_ptr;
        memcpy(fdata.data + fdata.size, buf, was_read);
        fdata.size += was_read;
        fdata.data[fdata.size] = '\0';
    }
    return fdata;
}
