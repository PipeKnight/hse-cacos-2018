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

int Read(int fd, char *ptr, int size) {
    return make_syscall(__NR_read, fd, ptr, size);
}

int Write(int fd, char *ptr, int size) {
    return make_syscall(__NR_write, fd, ptr, size);
}

void Exit(int code) {
    make_syscall(__NR_exit, code, 0, 0);
}

void *Brk(int increment) {
    return make_syscall(__NR_brk, increment, 0, 0);
}

void WriteBuf(char *begin, char *end, char *buf) {
    for (unsigned i = 0; i < end - begin; ++i) {
        buf[i] = *(end - i - 1);
    }
    int nwritten = Write(STDOUT, buf, end - begin);
    while (nwritten != end - begin) {
        nwritten += Write(STDOUT, buf + nwritten, end - begin - nwritten);
    }
}

void Revert(char *begin, char *end) {
    while (begin < end) {
        *begin ^= *end;
        *end ^= *begin;
        *begin ^= *end;
        ++begin;
        --end;
    }
}

int main() {
    char buf[BUFFERSIZE];
    int cap = BUFFERSIZE;
    int nread = 1;
    char *begin = Brk(0);
    char *cursb = begin + 1;
    char *end = Brk((void*)begin + cap);
    *cursb = '\n';
    ++cursb;
    while (nread >= 0) {
        nread = Read(STDIN, cursb, end - cursb);
        if (nread <= 0) {
            break;
        }
        if (nread == end - cursb) {
            cap *= 2;
            end = Brk(begin + cap);
        }
        cursb += nread;
    }
    if (*(cursb - 1) == '\n') {
        --cursb;
    }
    char *curbl = cursb;
    while (begin < curbl) {
        end = curbl;
        --curbl;
        while (*curbl != '\n' && curbl > begin) {
            --curbl;
        }
        Revert(curbl + 1, end - 1);
    }
    end = cursb;
    for (char *i = cursb; i > begin + 1; --i) {
        if (end - i == BUFFERSIZE) {
            WriteBuf(i, end, buf);
            end = i;
        }
    }
    WriteBuf(begin + 1, end, buf);
    return 0;
}

void _start() {
    Exit(main());
}
