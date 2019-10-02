#include <stdio.h>
#include <stdlib.h>

struct BSearchResult
{
    size_t low;
    size_t high;
    int result;
};

struct BSearchResult
bsearch2(const void *key, const void *base, size_t nmemb, size_t size,
        int (*compar)(const void *p1, const void *p2, void *user), void *user) {
    struct BSearchResult res;
    if (nmemb == 0) {
        res.low = 0;
        res.high = 0;
        res.result = 0;
        return res;
    }
    int lowA = 0;
    int highA = nmemb;
    while (lowA < highA - 1) {
        size_t mid = (lowA + highA) / 2;
        if (compar(base + mid * size, key, user) > 0) {
            highA = mid;
        } else {
            lowA = mid;
        }
    }

    int lowB = -1;
    int highB = nmemb - 1;
    while (lowB < highB - 1) {
        size_t mid = (lowB + highB) / 2;
        if (compar(base + mid * size, key, user) >= 0) {
            highB = mid;
        } else {
            lowB = mid;
        }
    }

    res.low = highB;
    res.high = highA;
    res.result = (compar(base +  res.low * size, key, user) == 0);
    if (res.low == 0) {
        if (compar(base, key, user) > 0) {
            res.high = 0;
            res.result = 0;
        }
    }
    if (res.high == nmemb) {
        if (compar(base + (res.high - 1) * size, key, user) < 0) {
            res.low = nmemb;
            res.result = 0;
        }
    }
    return res;
}