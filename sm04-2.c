void normalize_path(char *buf) {
    int slash = 0;
    char *normalized = buf;
    while (1) {
        if (*buf == '/') {
            slash = 1;
        } else {
            if (slash == 1) {
                *normalized = '/';
                slash = 0;
                normalized++;
            }
            *normalized = *buf;
            normalized++;
        }
        if (*buf == '\0') {
            break;
        }
        buf++;
    }
}
