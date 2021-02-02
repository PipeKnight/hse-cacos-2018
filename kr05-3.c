#include <string.h>

int parse_rwx_permissions(const char *str) {
    if (str == NULL) {
        return -1;
    }
    char sample[] = "rwxrwxrwx";
    if (strlen(str) != sizeof(sample) - 1) {
        return -1;
    }
    unsigned int rights = 0;     
    for (unsigned long i = 0; i != sizeof(sample) - 1; ++i) {
        if (str[i] == sample[i]) {
            rights |= 1;
            rights <<= 1;
        } else if (str[i] == '-') {
            rights <<= 1;
        } else {
            return -1;
        }
    }
    return rights >> 1;
}
