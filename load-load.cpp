#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> x(0);
std::atomic<int> y(0);

void thread1() {
    int a = y.load(std::memory_order_relaxed);
    if (a == 0) {
        std::cout << "Load-Load Reordering Detected!" << std::endl;
    }
    int b = x.load(std::memory_order_relaxed);
}

void thread2() {
    x.store(1);
    y.store(1);
}

int main() {

    std::thread t1(thread1);
    std::thread t2(thread2);
    
    t1.join();
    t2.join();

    
    return 0;
}
