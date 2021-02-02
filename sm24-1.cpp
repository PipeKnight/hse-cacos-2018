#include <cstdio>
#include <thread>
#include <vector>
#include <mutex>

enum
{
    N_THREADS = 3,
    N_PROCESS = 1000000,
    MIN_ADD = 80,
    STEP = 20,
    MIN_DEC = 90
};


std::mutex mx;
std::vector<double> arr(3, 0);

void thread_main(size_t id_add, size_t id_dec, double to_add, double to_dec) {
    for (int i = 0; i != N_PROCESS; ++i) {
        std::lock_guard<std::mutex> lock(mx);
        arr[id_add] += to_add;
        arr[id_dec] -= to_dec;
    }
    return;
}

int main() {
    std::vector<std::thread> threads(N_THREADS);
    for (size_t i = 0; i != threads.size(); ++i) {
        threads[i] = std::thread(thread_main, i, (i + 1) % arr.size(), MIN_ADD + i * STEP, MIN_DEC + i * STEP);
    }
    for (auto &th: threads) {
        th.join();
    }
    for (double x: arr) {
        printf("%.10g\n", x);
    }
    return 0;
}
