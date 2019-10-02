#include <stdio.h>
#include <stdlib.h>

static int cmp(const void *p1, const void *p2, void *th)
{
    const int a = *(const int *)p1;
    const int b = *(const int *)p2;
    int *data = (int*) th;
    if(data[a] > data[b]) {
        return 1;
    }
    if(data[a] < data[b]) {
        return -1;
    }
    return a - b;
}

void process(const size_t count, int *data, int *order)
{
    for (int i = 0; i < count; i++) {
        order[i] = i;
    }
    qsort_r(order, count, sizeof(*order), cmp, data);
}