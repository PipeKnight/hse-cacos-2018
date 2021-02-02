#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

enum { MAX_THREAD = 10 };

pthread_t threads[MAX_THREAD];

uint64_t safe_mod(uint64_t a, uint64_t b, uint64_t n) {
    a %= n;
    b %= n;
    uint64_t sum = a + b;
    if (sum < a || sum < b) {
        return ((~((uint64_t) 0) % n + 1) + sum) % n;
    }
    return sum % n;
}

void *thread_main(void *ptr) {
    char *name = *((char **) ptr);
    FILE *file = fopen(name, "r");
    uint64_t a, b, n;
    fscanf(file, "%" SCNu64 "%" SCNu64 "%" SCNu64, &a, &b, &n);
    printf("%" PRIu64 "\n", safe_mod(a, b, n));
    fclose(file);
    return 0;
}

int main(int argc, char **argv) {
    pthread_t *cur_thread = threads;
    for (int i = argc - 1; i > 0; --i) {
        pthread_create(cur_thread, NULL, &thread_main, argv + i);
        pthread_join(*cur_thread, NULL);
        cur_thread++;
    }
    return 0;
}
