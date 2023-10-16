/*
LOAD-LOAD reordering

S(x)=1 -> L(x)=1 -> S(y)=1 -> L(y)=1 [Correct order for load load]    => Follow Sequencial Consistency
S(y)=1 -> L(y)=0 -> S(x)=1 -> L(x)=1 [Reordered load load]            => Not sequencial Consistency
*/

#include <iostream>
#include <thread>
#include <atomic>

volatile std::atomic<int> x(0);
volatile std::atomic<int> y(0);

void thread1() {
    do{
        if ( x.load(std::memory_order_relaxed) == 0 ) {
            if( y.load(std::memory_order_relaxed) == 1){
                std::cout << "load-load detected";
                return;
            }
        }
        else
            return;
    }while(true);
}

// Assumption: here store-store instructions are not reordered 
void thread2() {
    x.store(1,std::memory_order_relaxed);
    y.store(1,std::memory_order_relaxed);
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
