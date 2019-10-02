#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

enum { BUFFERSIZE = 4096 };

struct FileContent error(struct FileContent *result) {
    if (result->data != NULL) {
        free(result->data);
    }
    struct FileContent err = {-1, NULL};
    return err;
}

struct FileContent read_file(int fd) {
    struct FileContent result;
    result.size = 0;
    result.data = NULL;
    char buf[BUFFERSIZE];
    int fread;
    while ((fread = read(fd, buf, BUFFERSIZE)) != 0) {
        if (fread == -1) {
            return error(&result);
        }
        char *newmem = realloc(result.data, result.size + fread);
        if (newmem == NULL) {
            return error(&result);
        }
        result.data = newmem;
        memcpy(result.data + result.size, buf, fread);
        result.size += fread;
    }
    char *newmem = realloc(result.data, result.size + 1);
    if (newmem == NULL) {
        return error(&result);
    }
    result.data = newmem;
    result.data[result.size] = '\0';
    return result;
}
