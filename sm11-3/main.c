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

typedef struct FileReadState
{
    int fd;              // "файловый дескриптор", для чтения со стандартного потока ввода - 0
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    int lc;              // последний считанный символ
    
    int iter;
    int empty;
    int eof;
} FileReadState;

FileReadState MyFileReadState = { STDIN, buffer, BUFFERSIZE, 0, 0, 1, 0 };
FileReadState *stin = &MyFileReadState;


int nextchar() {
    if (stin->eof) {
        return -1;
    }
    if (stin->empty == 0) {
        if (stin->iter == stin->bufsize) {
            stin->empty = 1;
            stin->iter = 0;
        } else {
            stin->lc = stin->buf[stin->iter];
            stin->iter++;
        }
    }
    if (stin->iter == 0) {
        int count = Read(stin->fd, stin->buf, BUFFERSIZE);
        if (count > 0) {
            stin->bufsize = count;
            stin->empty = 0;
            stin->lc = stin->buf[stin->iter];
            stin->iter++;
        } else {
            stin->eof = 1;
            return -1;
        }
    }
    return stin->lc;
}

int lastchar() {
    return stin->lc;
}