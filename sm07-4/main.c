#include<inttypes.h>
#include<stdint.h>
#include<stdlib.h>

enum 
{
    MULT = 1103515245,
    SHIFT = 12345,
    MOD = (1 << 31)
};

struct RandomOperations 
{
    void (*destroy) (void *);
    int (*next) (void *);
};

static struct RandomOperations Ops;

typedef struct RandomGenerator
{
    uint32_t cur;
    struct RandomOperations *ops;
} RandomGenerator;

int operation_next(void *v) {
    RandomGenerator *r = v;
    return r->cur = (r->cur * MULT % MOD + SHIFT) % MOD;
}

void operation_destroy(void *v) {
    RandomGenerator *r = v;
    free(r);
}

RandomGenerator * random_create(int seed) {
    RandomGenerator *rg = calloc(1, sizeof(RandomGenerator));
    rg->cur = seed;
    rg->ops = &Ops;
    Ops.destroy = operation_destroy;
    Ops.next = operation_next;
    return rg;
}