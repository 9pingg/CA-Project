/*
LOAD-STORE reordering

S(x)=1 -> S(y)=1 -> L(x)=1 -> L(y)=1 [Correct order for load load]
L(y)=0 -> S(x)=1 -> S(y)=1 -> L(x)=1 [Reordered load store]
L(x)=0 -> S(x)=1 -> S(y)=1 -> L(y)=1 [Reordered store load]
*/

#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> x(0);
std::atomic<int> y(0);


void thread1() {
    x.store(1, std::memory_order_relaxed);
    int a = y.load(std::memory_order_relaxed);
    if (a == 0) {
        std::cout << "load-store/store-load detected";
    }
}

void thread2() {
    y.store(1, std::memory_order_relaxed);
    int b = x.load(std::memory_order_relaxed);
    if (b == 0) {
        std::cout << "load-store/store-load detected";
    }
}

int main() {

    // creating threads and executing them
    std::thread t1(thread1);
    std::thread t2(thread2);

    // waiting for thread to join
    t1.join();
    t2.join();
    
    return 0;
}
