#include <stdio.h>
#include <pthread.h>

struct Info 
{
    int n;
    pthread_t prev_id;
};

void *thread_main(void *ptr) {
    struct Info *new_ptr = ptr;
    if (new_ptr->n != 0) {
        pthread_join(new_ptr->prev_id, NULL);
    }
    printf("%d\n", new_ptr->n);
    return 0;
}

int main() {
    enum { N_THREAD = 10 };
    pthread_t cur_thread = 0;
    struct Info thread_info[N_THREAD];
    for (int i = 0; i != N_THREAD; ++i) {
        thread_info[i].n = i;
        thread_info[i].prev_id = cur_thread;
        pthread_create(&cur_thread, NULL, &thread_main, thread_info + i);
    }
    pthread_join(cur_thread, NULL);
    return 0;
}
