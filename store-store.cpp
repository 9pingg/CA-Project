#include <iostream>
#include <thread>
#include <atomic>
#include <unistd.h>

volatile std::atomic<int> x(0);
volatile std::atomic<int> y(0);



// X86 archetecture
void thread1() {
    x.store(1, std::memory_order_relaxed);
    y.store(1, std::memory_order_relaxed);
}

void thread2() {
    while(x.load() == 0){
        if(y.load() == 1){
            std::cout << "Store-Store Reordering Detected!" << std::endl;
            break;
        }
    }
}

int main() {
    
    std::thread t1(thread1);
    std::thread t2(thread2);
    
    t1.join();
    t2.join();
    
    return 0;
}
