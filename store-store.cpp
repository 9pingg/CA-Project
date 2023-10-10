#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> x(0);
std::atomic<int> y(0);

void thread1() {
    x.store(1, std::memory_order_relaxed);
    y.store(1, std::memory_order_relaxed);
}

void thread2() {
    while (y.load(std::memory_order_relaxed) != 1);
    if (x.load(std::memory_order_relaxed) == 0) {
        std::cout << "Store-Store Reordering Detected!" << std::endl;
    }
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);
    
    t1.join();
    t2.join();
    
    return 0;
}
