#include <pthread.h>
#include <stdio.h>

void *thread_main(void *ptr) {
    int numb;
    if (scanf("%d", &numb) != EOF) {
        pthread_t cur_thread;
        pthread_create(&cur_thread, NULL, &thread_main, NULL);
        pthread_join(cur_thread, NULL);
        printf("%d\n", numb);
    }
    return 0;
}

int main() {
    pthread_t cur_thread;
    pthread_create(&cur_thread, NULL, &thread_main, NULL);
    pthread_join(cur_thread, NULL);
    return 0;
}
