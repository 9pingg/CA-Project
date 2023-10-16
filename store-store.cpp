/*
STORE-STORE reordering

S(x)=1 -> L(x)=1 -> S(y)=1 -> L(y)=1 [Correct order for store store]   
S(y)=1 -> L(x)=0 -> S(x)=1 -> L(y)=1 [Reordered store store]            
*/

#include <iostream>
#include <thread>
#include <atomic>
#include <unistd.h>

volatile std::atomic<int> x(0);
volatile std::atomic<int> y(0);


// X86 archetecture
// differnce between cohereance and consistancy
// why reordering happen at arch level
void thread1() {
    x.store(1);
    y.store(1);
}

// Assumption: here load-load instructions are not reordered
void thread2() {
    while(x.load() == 0){
        if(y.load() == 1){
            std::cout << "store-store detected";
            break;
        }
    }
}

int main() {

    // std::cout << "init" << std::endl;
    
    std::thread t2(thread2);
    std::thread t1(thread1);
    
    t1.join();
    t2.join();
    
    return 0;
}
