#include <cstdio>
#include <thread>
#include <mutex>
#include <cstdint>
#include <cinttypes>
#include <future>
#include <utility>
#include <vector>

bool isPrime(uint64_t n) {
    if (n == 2) {
        return true;
    }
    if (n < 2 || n % 2 == 0) {
        return false;
    }
    for (uint64_t i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void thread_main(uint64_t low, uint64_t high, std::vector<std::promise<uint64_t>> proms) {
    uint64_t primeCounter = 0;
    for (uint64_t numb = low; numb <= high; numb++) {
        if (isPrime(numb)) {
            if (primeCounter < proms.size()) {
                proms[primeCounter].set_value(numb);
            }
            primeCounter++;
            if (primeCounter == proms.size()) {
                return;
            }
        }
    }
    try {
        throw high;
    } catch (...) {
        proms[primeCounter].set_exception(std::current_exception());
    }
    return;
}

int main() {
    uint64_t low, high;
    scanf("%" SCNu64 "%" SCNu64, &low, &high);
    int32_t count;
    scanf("%" SCNd32, &count);
    std::vector<std::promise<uint64_t>> proms(count);
    std::vector<std::future<uint64_t>> futs(count);
    for (size_t i = 0; i != futs.size(); ++i) {
        futs[i] = proms[i].get_future();
    }
    std::thread thr;
    try {
        thr = std::thread(thread_main, low, high, std::move(proms));
        for (int32_t i = 0; i != count; ++i) {
            futs[i].wait();
            printf("%" PRIu64 "\n", futs[i].get());
            fflush(stdout);
        }
    } catch (uint64_t code) {
        printf("%" PRIu64 "\n", code);
    }
    thr.join();
    return 0;
}
