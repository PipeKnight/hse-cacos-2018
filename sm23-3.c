#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdatomic.h>

enum
{
    N_THREAD = 100,
    N_ITEM = 1000
};

struct Item
{
    struct Item *next;
    long long value;
};

_Atomic (struct Item *) item;

void *thread_main(void *ptr) {
    int id = *((int *) ptr);
    for (int i = id * N_ITEM; i != (id + 1) * N_ITEM; ++i) {
        struct Item *new_item = calloc(1, sizeof(*new_item));
        new_item->value = i;
        new_item->next = NULL;
        atomic_exchange(&item, new_item)->next = new_item;
        sched_yield();
    }
    return 0;
}

int main() {
    struct Item root = { NULL, 0 };
    item = &root;
    pthread_t threads[N_THREAD];
    int ids[N_THREAD];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, sysconf(_SC_THREAD_STACK_MIN));
    for (int i = 0; i != N_THREAD; ++i) {
        ids[i] = i;
        pthread_create(threads + i, &attr, &thread_main, ids + i);
    }
    pthread_attr_destroy(&attr);
    for (int i = 0; i != N_THREAD; ++i) {
        pthread_join(threads[i], NULL);
    }
    item = NULL;
    struct Item *cur = root.next;
    while (cur != NULL) {
        printf("%lld\n", cur->value);
        struct Item *to_free = cur;
        cur = cur->next;
        free(to_free);
    }
    return 0;
}
