#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

enum { N = 6 };

pthread_t ids[N];
pthread_t ids2[N];

void *func2(void *arg)
{
    pause();
    return NULL;
}

void *func(void *arg)
{
    int serial = (int) (intptr_t) arg;
    pthread_join(ids2[serial], NULL);
    printf("%d\n", serial);
    fflush(stdout);
    if (serial == 5) {
        pthread_cancel(ids2[3]);
    } else if (serial == 3) {
        pthread_cancel(ids2[1]);
    } else if (serial == 1) {
        pthread_cancel(ids2[0]);
    } else if (serial == 0) {
        pthread_cancel(ids2[4]);
    } else if (serial == 4) {
        pthread_cancel(ids2[2]);
    }
    return NULL;
}

int main()
{
    for (int i = 0; i < N; ++i) {
        pthread_create(&ids2[i], NULL, func2, NULL);
    }
    for (int i = 0; i < N; ++i) {
        pthread_create(&ids[i], NULL, func, (void*) (intptr_t) i);
    }

    pthread_cancel(ids2[5]); 
    
    for (int i = 0; i != N; ++i) {
        pthread_join(ids[i], NULL);
    }
    return 0;
}
