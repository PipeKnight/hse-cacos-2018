#include <stdio.h>
#include <pthread.h>

enum
{
    N_THREAD = 3,
    N_PROCESS = 1000000,
};

double arr[N_THREAD];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_main(void *ptr) {
    int thread_id = *((int *) ptr);
    for (int i = 0; i != N_PROCESS; ++i) {
        pthread_mutex_lock(&mutex);
        arr[thread_id] += (thread_id + 1) * 100;
        arr[(thread_id + 1) % N_THREAD] -= (thread_id + 1) * 100 + 1;
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}

int main() {
    pthread_t cur_thread[N_THREAD];
    int ids[N_THREAD];
    for (int i = 0; i != N_THREAD; ++i) {
        ids[i] = i;
        pthread_create(cur_thread + i, NULL, &thread_main, ids + i);
    }
    for (int i = 0; i != N_THREAD; ++i) {
        pthread_join(cur_thread[i], NULL);
    }
    for (int i = 0; i != N_THREAD; ++i) {
        printf("%.10g\n", arr[i]);
    }
    return 0;
}
