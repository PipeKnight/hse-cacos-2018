#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <stdint.h>

uint64_t cur_prime = 0;
int flag = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int is_prime(uint64_t n) {
    if (n == 2) {
        return 1;
    }
    if (n < 2 || n % 2 == 0) {
        return 0;
    }
    for (uint64_t i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void *thread_main(void *ptr) {
    uint64_t base = *((uint64_t *) ptr);
    while (1) {
        if (is_prime(base)) {
            pthread_mutex_lock(&mutex);
            flag = 1;
            cur_prime = base;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex);
        }
        base++;
    }
    return 0;
}

int main() {
    uint64_t base;
    int32_t count;
    scanf("%" SCNu64 " %" SCNd32, &base, &count);
    pthread_t cur_thread;
    pthread_create(&cur_thread, NULL, &thread_main, &base);
    for (int32_t i = 0; i < count; ++i) {
        uint64_t to_print = 0;
        pthread_mutex_lock(&mutex);
        if (flag == 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        to_print = cur_prime;
        pthread_mutex_unlock(&mutex);
        printf("%" PRIu64 "\n", to_print);
        flag = 0;
    }
    return 0;
}
