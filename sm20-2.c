#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sock_in;
    sock_in.sin_family = AF_INET;
    int port;
    sscanf(argv[2], "%d", &port);
    sock_in.sin_port = htons(port);
    struct hostent *he = gethostbyname(argv[1]);
    memcpy(&sock_in.sin_addr, he->h_addr_list[0], sizeof(sock_in.sin_addr));
    connect(fd, (struct sockaddr *) &sock_in, sizeof(sock_in));
    int fdin = dup(fd);
    FILE *stream_in = fdopen(fdin, "r");
    FILE *stream_out = fdopen(fd, "w");
    if (fprintf(stream_out, "%s\n", argv[3]) == EOF) {
        fclose(stream_in);
        fclose(stream_out);
        return 0;
    }
    fflush(stream_out);
    unsigned long long max_numb = 0;
    if (fscanf(stream_in, "%llu", &max_numb) == EOF) {
        fclose(stream_in);
        fclose(stream_out);
        return 0;
    }
    fflush(stream_in);
    for (unsigned long long i = 0; i <= max_numb; ++i) {
        if (fprintf(stream_out, "%llu\n", i) == EOF) {
            fclose(stream_in);
            fclose(stream_out);
            return 0;
        }
        fflush(stream_out);
    }
    unsigned long long to_print = 0;
    if (fscanf(stream_in, "%llu", &to_print) == EOF) {
        fclose(stream_in);
        fclose(stream_out);
        return 0;
    }
    fflush(stream_in);
    fclose(stream_in);
    fclose(stream_out);
    printf("%llu\n", to_print);
    fflush(stdout);
    return 0;
}
