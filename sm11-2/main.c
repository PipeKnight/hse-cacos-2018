#include <asm/unistd.h>

enum { STDIN = 0, STDOUT = 1, STDERR = 2, ZERO = 0, DIFF = 32 };

int make_syscall(int eax, int ebx, int ecx, int edx) {
    volatile int result = 0;
    asm volatile (
        "mov    %1, %%eax\n"
        "mov    %2, %%ebx\n"
        "mov    %3, %%ecx\n"
        "mov    %4, %%edx\n"
        "int    $0x80\n"
        "mov    %%eax, %0\n"
        :"=g"(result)
        :"g"(eax), "g"(ebx), "g"(ecx), "g"(edx)
        :"eax", "ebx", "ecx", "edx"
    );
    return result;
}

int Read(int fd, char *ptr, int size) {
    return make_syscall(__NR_read, fd, (int)ptr, size);
}

int Write(int fd, char *ptr, int size) {
    return make_syscall(__NR_write, fd, (int)ptr, size);
}

void Exit(int code) {
    make_syscall(__NR_exit, code, ZERO, ZERO);
}

int main() {
    char buf = ZERO;
    while(Read(STDIN, &buf, 1) != ZERO) {
        if('a' <= buf && buf <= 'z') {
            buf -= DIFF;
        }
        Write(STDOUT, &buf, 1);
    }
    return 0;
}

void _start() {
    Exit(main());
}
