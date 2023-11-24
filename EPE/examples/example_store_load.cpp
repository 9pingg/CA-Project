
#include <iostream>
#include <thread>
#include <atomic>
#include <unistd.h>
#include "memo.h"

std::atomic<int> x(0);
std::atomic<int> y(0);

void thread1() {
    memo::init_thread();

    memo::store(x, 1, "S1");
    int a = memo::load(x, "L1");
    std::cout<<"Y value: "<<a<<std::endl;
    // if (a == 0) {
    //     std::cout << "load-store/store-load detected";
    // }
}

void thread2() {
    memo::init_thread();

    memo::store(y, 1, "S2");
    int b = memo::load(y, "L2");
    std::cout<<"X value: "<<b<<std::endl;
    // if (b == 0) {
    //     std::cout << "load-store/store-load detected";
    // }
}

int main() {

    memo::init_runtime();
    memo::activate_tso();
    memo::activate_bypassing();

    // creating threads and executing them
    std::thread t1(thread1);
    std::thread t2(thread2);

    // waiting for thread to join
    t1.join();
    t2.join();

    memo::finalize_runtime();
    return 0;
}
