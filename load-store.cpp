#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> x(0);
std::atomic<int> y(0);

void thread1() {
    x.store(1, std::memory_order_relaxed);
    int a = y.load(std::memory_order_relaxed);
    if (a == 0) {
        std::cout << "Load-Store and Store-Load Reordering Detected!" << std::endl;
    }
}

void thread2() {
    y.store(1, std::memory_order_relaxed);
    int b = x.load(std::memory_order_relaxed);
    if (b == 0) {
        std::cout << "Load-Store and Store-Load Reordering Detected!" << std::endl;
    }
}

int main() {
    std::thread t1(thread1);
    std::thread t2(thread2);
    
    t1.join();
    t2.join();
    
    return 0;
}
