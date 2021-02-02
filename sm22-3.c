#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <limits.h>

void *thread_main(void *ptr) {
    int numb = 0;
    long long *new_ptr = ptr;
    long long sum = 0;
    while (scanf("%d", &numb) != EOF) {
        sum += numb;
        sched_yield();
    }
    *new_ptr = sum;
    return 0;
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    long long **sum = realloc(NULL, n * sizeof(*sum));
    pthread_t *threads = realloc(NULL, n * sizeof(*threads));
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    pthread_attr_setguardsize(&attr, 0);
    for (int i = 0; i != n; ++i) {
        sum[i] = realloc(NULL, sizeof(*sum[i]));
        pthread_create(threads + i, &attr, &thread_main, sum[i]);
    }
    pthread_attr_destroy(&attr);
    for (int i = 0; i != n; ++i) {
        pthread_join(threads[i], NULL);
    }
    free(threads);
    long long total = 0;
    for (int i = 0; i != n; ++i) {
        total += *sum[i];
        free(sum[i]);
    }
    printf("%lld\n", total);
    fflush(0);
    return 0;
}
