#include <asm/unistd.h>

enum { STDIN = 0, STDOUT = 1, STDERR = 2, ZERO = 0, BUFFERSIZE = 4096 };

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

int Read(int fd, char *ptr, int iter) {
    return make_syscall(__NR_read, fd, (int)ptr, iter);
}

int Write(int fd, char *ptr, int iter) {
    return make_syscall(__NR_write, fd, (int)ptr, iter);
}

void Exit(int code) {
    make_syscall(__NR_exit, code, ZERO, ZERO);
}

unsigned char buffer[BUFFERSIZE];

typedef struct FileWriteState
{
    int fd;              // "файловый дескриптор", для вывода на стандартный поток вывода - 1
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    int iter;
} FileWriteState;

FileWriteState MyFileWriteState = { STDOUT, buffer, BUFFERSIZE, 0 };
FileWriteState *stout = &MyFileWriteState;

__attribute__((fastcall))
void writechar(int c, FileWriteState *out) {
    if (out->iter == out->bufsize) {
        flush(out);
        out->iter = 0;
    }
    out->buf[out->iter] = c;
    out->iter++;
}

__attribute__((fastcall))
void flush(FileWriteState *out) {
    Write(out->fd, out->buf, out->iter);
}
