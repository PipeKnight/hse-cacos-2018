#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <limits.h>

int main() {
    enum { BUF_SIZE = 1000 + 1 };
    char host[BUF_SIZE], service[BUF_SIZE];
    while (scanf("%1000s %1000s", host, service) != EOF) {
        struct addrinfo hints = {};
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        struct addrinfo *info;
        int err = 0;
        if ((err = getaddrinfo(host, service, &hints, &info)) != 0) {
            printf("%s\n", gai_strerror(err));
            fflush(stdout);
            continue;
        }
        struct sockaddr_in* min_loc_addr = NULL;
        while (info != NULL) {
            struct sockaddr_in *cur_sock = (struct sockaddr_in *) info->ai_addr;
            if (min_loc_addr == NULL
                    || ntohl(cur_sock->sin_addr.s_addr) <= ntohl(min_loc_addr->sin_addr.s_addr)) {
                min_loc_addr = cur_sock;
            }
            info = info->ai_next;
        }
        printf("%s:%hu\n", inet_ntoa(min_loc_addr->sin_addr), ntohs(min_loc_addr->sin_port));
        fflush(stdout);
        freeaddrinfo(info);
    }
    return 0;
}
