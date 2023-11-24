import os
import subprocess
import sys

def check_reordering(file_name, num_runs):
    count_store_store = 0
    count_store_load = 0
    count_load_store = 0
    count_load_load = 0
    count_initializing = 0

    for i in range(num_runs):
        output = subprocess.check_output(["./run"]).decode("utf-8")
        if "store-store detected" in output:
            count_store_store += 1
        if "load-store/store-load detected" in output:
            count_store_load += 1
        if "load-store detected" in output:
            count_load_store += 1
        if "load-load detected" in output:
            count_load_load += 1
    
        count_initializing += 1

    if file_name == "store-store.cpp":
        print(f"Count of 'store-store' reordering detected: {count_store_store}")
    elif file_name == "load-store.cpp":
        print(f"Count of 'load-store/store-load' reordering detected: {count_store_load}")
    elif file_name == "load-load.cpp":
        print(f"Count of 'load-load' reordering detected: {count_load_load}")

    print(f"Number of runs: {count_initializing}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python script.py <cpp_file> <number_of_runs>\nEnter the memory reordering you want to check (load-load.cpp, store-store.cpp, load-store.cpp)")
        exit(1)
    file_name = sys.argv[1]
    num_runs = int(sys.argv[2])
    if not os.path.isfile(file_name):
        print(f"Error: File '{file_name}' not found.")
        exit(1)

    compile_command = f"g++ {file_name} -o run"
    subprocess.run(compile_command, shell=True)
    check_reordering(file_name, num_runs)
    os.remove("run")
