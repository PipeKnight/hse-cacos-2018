int my_read(char *c) {
    int was_read;
    asm volatile(
        "movl   $3, %%eax\n"
        "movl   $0, %%ebx\n"
        "movl   %1, %%ecx\n"
        "movl   $1, %%edx\n"
        "int    $0x80\n"
        "movl   %%eax, %0"
        : "=g"(was_read)
        : "g"(c)
        : "memory", "%eax", "%ebx", "%ecx", "%edx");
    return was_read;
}

void my_exit(int code) {
    asm volatile(
        "movl   $1, %%eax\n"
        "movl   %0, %%ebx\n"
        "int    $0x80\n"
        :
        : "g"(code)
        : "memory", "%eax", "%ebx");
}

int my_write(char *c) {
    int was_written = 0;
    asm volatile(
        "movl   $4, %%eax\n"
        "movl   $1, %%ebx\n"
        "movl   %1, %%ecx\n"
        "movl   $1, %%edx\n"
        "int    $0x80\n"
        "movl   %%eax, %0"
        : "=g"(was_written)
        : "g"(c)
        : "memory", "%eax", "%ebx", "%ecx", "%edx");
    return was_written;
}

void _start() {
    char c = 42;
    while (my_read(&c) != 0) {
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
        my_write(&c);
    }
    my_exit(0);
}
