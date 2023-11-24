
#include <iostream>
#include <thread>
#include <atomic>
#include <unistd.h>
#include "memo.h"

std::atomic<int> x(0);
std::atomic<int> y(0);
// load-load case
void thread1() {
    memo::init_thread();

    int a = memo::load(x, "L1");
    int b = memo::load(y, "L2");
    
    std::cout<<"X value: "<<a<<std::endl;
    std::cout<<"Y value: "<<b<<std::endl;
    
}

void thread2() {
    memo::init_thread();

    memo::store(x, 1, "S1");
    memo::store(y, 1, "S2");

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
