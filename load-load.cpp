#include <iostream>
#include <thread>
#include <atomic>

volatile std::atomic<int> x(0);
volatile std::atomic<int> y(0);

void thread1() {
    int flag = y.load(std::memory_order_relaxed);
    int data = x.load(std::memory_order_relaxed);
    if ( flag==1 && data == 0) {
        std::cout << "Load-Load Reordering Detected!" << std::endl;
    }
}

void thread2() {
    // __asm__ __volatile__ ("movl %1, %0;"
    // :"=r"(x) /* related to %0*/
    // :"r"(11) /* related to %1*/
    // :);
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
