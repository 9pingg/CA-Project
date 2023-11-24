# Memory Reordering:

Demonstration of the reordering using memory litmus test:
* Store-store reordering.
* Load-load reordering
* Load-store and store load reordering.
## Memory Litmus Test
Memory litmus tests are small multi-threaded programs that are designed to detect possible memory reorderings by threads. They work by setting up certain ordering conditions between memory operations done by multiple threads, and then checking if those orderings held properly at the end.

In this project, We have implemented 3 different litmus tests to detect the following types of memory reorderings:

### Store-store reordering: 
Checks if ordering between store operations done by two different threads is maintained or reordered. This is implemented in store_store_litmus.cpp.
### Load-load reordering: 
Checks ordering between load operations by two threads. Implemented in load_load_litmus.cpp.
### Load-store/Store-load reordering: 
Checks ordering of a combination of loads and stores across threads. Implemented in load_store_litmus.cpp.

## 
To test reordering , run script.py which automatically compiles and runs each litmus executable multiple times. It checks the output to see if any reordering was detected.
```
python3 script.py <cpp_file> <num_runs>
```

Replace <cpp_file> with the name of your C++ source litmus test and <num_runs> with the desired number of runs.

