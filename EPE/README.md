# Total Store Order (TSO) memory model 
* Implemented Library based runtime for ensuring Sequential Consistency and Total Store Order memory model.

* The library provides runtime primitives for TSO that can be used to coordinate shared memory access and avoid reorderings.

## Steps to run examples

The `examples/` directory contains additional memory litmus tests showing how the TSO memory model prevents reorderings.
Follow the followning steps to run the example
```
$ make file=<cpp_file>  [To compile]
$ ./example                 [To run]
```
Here example_name can be one of the following
- example_load.c
- example_store.c
- example_store_load.c
- example.c