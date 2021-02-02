#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

int main(int argc, char *argv[]) {
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sock_in, sock_client;
    sock_in.sin_family = AF_INET;
    int port;
    sscanf(argv[1], "%d", &port);
    sock_in.sin_port = htons(port);
    sock_in.sin_addr.s_addr = INADDR_ANY;
    bind(fd, (struct sockaddr *) &sock_in, sizeof(sock_in));
    listen(fd, 5);
    unsigned int alen = sizeof(sock_client);
    int32_t sum = 0;
    while (1) {
        int fd_in = accept(fd, (struct sockaddr *) &sock_client, &alen);
        int32_t numb = 0;
        while (read(fd_in, &numb, sizeof(numb)) != 0) {}
        close(fd_in);
        if (numb == 0) {
            break;
        }
        sum += (int32_t) ntohl(numb);
    }
    printf("%" PRId32 "\n", sum);
    close(fd);
    return 0;
}
