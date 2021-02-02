#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <sched.h>

struct Info
{
    int n;
    pthread_t thread_id;
};

enum
{
    MAX_THREAD = 100
};

struct Info *thread_infos = NULL;
int fd_threads[MAX_THREAD][2];
int fd_main[2];
int order;
int count;

void *thread_main(void *ptr) {
    struct Info *new_ptr = ptr;
    while (1) {
        int cur_order;
        read(fd_threads[new_ptr->n][0], &cur_order, sizeof(cur_order));
        sched_yield();
        if (cur_order != order) {
            fprintf(stderr, "Wrong order");
            exit(1);
        }
        int32_t numb;
        if (scanf("%" SCNd32, &numb) != EOF) {
            printf("%d %" PRId32 "\n", new_ptr->n, numb);
            order = (numb % count + count) % count;
            write(fd_threads[order][1], &order, sizeof(order));
        } else {
            write(fd_main[1], &(new_ptr->thread_id), sizeof(new_ptr->thread_id));
            for (int i = 0; i != count; ++i) {
                if (i != new_ptr->n) {
                    pthread_cancel(thread_infos[i].thread_id);
                }
            }
            return 0;
        }
    }
}

int main(int argc, char *argv[]) {
    count = atoi(argv[1]);
    struct Info *arr = calloc(count, sizeof(*arr));
    thread_infos = arr;
    order = -1;
    pipe(fd_main);
    for (int i = 0; i != count; ++i) {
        thread_infos[i].n = i;
        pipe(fd_threads[i]);
        pthread_create(&thread_infos[i].thread_id, NULL, thread_main, thread_infos + i);
    }
    order = 0;
    write(fd_threads[order][1], &order, sizeof(order));
    pthread_t last_thread = 0;
    read(fd_main[0], &last_thread, sizeof(last_thread));
    pthread_join(last_thread, NULL);
    close(fd_main[0]);
    close(fd_main[1]);
    for (int i = 0; i != count; ++i) {
        close(fd_threads[i][0]);
        close(fd_threads[i][0]);
    }
    free(arr);
    return 0;
}

