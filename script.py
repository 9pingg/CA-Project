import os
import subprocess

count_store_store = 0
count_store_load = 0
count_load_store = 0
count_load_load = 0
count_initializing = 0

for i in range(1, 1001):
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

if count_store_store != 0:
    print(f"Count of 'store-store': {count_store_store}")
elif count_store_load != 0:
    print(f"Count of 'load-store/store-load': {count_store_load}")
elif count_load_load != 0:
    print(f"Count of 'load-load': {count_load_load}")

print(f"Number of runs: {count_initializing}")
