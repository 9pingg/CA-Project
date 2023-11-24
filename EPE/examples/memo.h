#include <bits/stdc++.h>
#include <pthread.h>
#include <iostream>
#include <atomic>
#include <iostream>
#include <deque>
#include <queue>
#include <thread>
#include <mutex>
#include <unordered_map>

#define MAX_LABEL_LEN 32

struct store_operation{
    std::atomic<int>*memory_pointer;
    int value;
    char label[MAX_LABEL_LEN];
};

// all the global variables for the runtime
std::mutex lock_switch;
bool tso;
bool bypass;
std::unordered_map<std::thread::id, std::deque<struct store_operation*>*> deques;
std::queue<const char*> global_order;

namespace memo
{
    // initialise the runtime 
    void init_runtime(){
        tso = false;
        bypass = false;
    }

    void init_thread(){
        std::thread::id thread_id = std::this_thread::get_id();
        deques[thread_id] = new std::deque<struct store_operation*>;
    }

    // drain the buffers and end the runtime
    void finalize_runtime(){
        // flush out the buffer before exiting
        for (const auto& pair : deques) {
            std::deque<struct store_operation*>* deque_ptr = pair.second;
            lock_switch.lock();
            for(struct store_operation* ops: *deque_ptr){
                ops->memory_pointer->store(ops->value);
                global_order.push(ops->label);
            }
            lock_switch.unlock();
        }

        // printing system info 
        std::cout <<"==========================\n\n";
        if(tso)
            std::cout << "[INFO] TSO ACTIVE\n\n";
        else
            std::cout << "[INFO] TSO NOT ACTIVE\n\n";
        if(bypass)
            std::cout << "[INFO] BYPASSING ACTIVE\n\n";
        else
            std::cout << "[INFO] BYPASSING NOT ACTIVE\n\n";
        
        // printing the global order
        printf("GLOBAL ORDER IS:\n");
            while (!global_order.empty()) {
            std::cout << global_order.front() << " -> ";
            global_order.pop();
        }
            std::cout << "Done\n\n";
        std::cout<<"==========================\n";
    }

    // activate tso
    void activate_tso(){
        tso = true;
    }

    // activate bypassing in tso
    void activate_bypassing(){
        bypass = true;
    }


    // load value from the atomic variable
    int load(std::atomic<int>& atomicVar, const char*label){
        int val;
        lock_switch.lock();
        // if there is no bypassing then do nothing
        if(!bypass){
            val = atomicVar.load();
            global_order.push(label);
            lock_switch.unlock();
            return val;
        }

        // tso and bypassing is active
        // check for latest values in the current store_queue 
        // if its present then take latest value [BYPASSING]
        std::thread::id thread_id = std::this_thread::get_id();
        int i=0;
        bool found =false;
        for(struct store_operation* sop: *deques[thread_id]){
            if(sop->memory_pointer == &atomicVar){
                found = true;
                val = sop->value;
            }
            i++;
        }
        if(!found){
            val = atomicVar.load();
        }
        global_order.push(label);
        lock_switch.unlock();
        return val;
    }

    // store value in the atomic variable
    void store(std::atomic<int>& atomicVar, int newValue, const char*label){
        // storing the value directly if tso is disabled
        lock_switch.lock();
        if(!tso){
            atomicVar.store(newValue);
            global_order.push(label);
            lock_switch.unlock();
            return;
        }
        
        // start storing the store_operations to execute
        std::thread::id thread_id = std::this_thread::get_id();
        struct store_operation *sop = new struct store_operation;
        strcpy(sop->label, label);
        sop->memory_pointer = &atomicVar;
        sop->value = newValue;
        deques[thread_id]->push_back(sop);

        lock_switch.unlock();
        return;
    }

}