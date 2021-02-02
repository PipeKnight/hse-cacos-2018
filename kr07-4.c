#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int fd_p1_p2[2], fd_p2_p4[2];
    uint32_t count = atol(argv[1]);
    uint32_t modulo = atol(argv[2]);
    pipe(fd_p2_p4);
    // P1
    if (fork() == 0) {
        pipe(fd_p1_p2);
        close(fd_p2_p4[0]);
        // P2
        if (fork() == 0) {
            close(fd_p1_p2[1]);
            dup2(fd_p1_p2[0], 0);
            close(fd_p1_p2[0]);
            dup2(fd_p2_p4[1], 1);
            close(fd_p2_p4[1]);
            execlp(argv[3], argv[3], NULL);
            close(0);
            close(1);
            _exit(127);
        }
        close(fd_p1_p2[0]);
        close(fd_p2_p4[1]);
        FILE *out_stream = fdopen(fd_p1_p2[1], "w");
        enum { BUF_SZ = 4096 };
        char local_buf[BUF_SZ];
        setbuf(out_stream, local_buf);
        for (uint32_t i = 1; i <= count; ++i) {
            uint32_t sqrt_mod = ((long long) i * i) % modulo;
            fprintf(out_stream, "%" PRIu32 "\t", sqrt_mod);
        }
        fflush(out_stream);
        fprintf(out_stream, "\n");
        fclose(out_stream);
        wait(NULL);
        return 0;
    }
    close(fd_p2_p4[1]);
    // P3
    if (fork() == 0) {
        // P4
        if (fork() == 0) {
            FILE *in_stream = fdopen(fd_p2_p4[0], "r");
            int c = 0;
            while ((c = getc_unlocked(in_stream)) != EOF) {
                if ((char) c == ' ') {
                    c = '\n';
                }
                putchar(c);
            }
            fclose(in_stream);
            return 0;
        }
        close(fd_p2_p4[0]);
        wait(NULL);
        return 0;
    }
    close(fd_p2_p4[0]);
    wait(NULL);
    wait(NULL);
    printf("%d\n", 0);
    return 0;
}
