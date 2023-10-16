#!/bin/bash

count_store_store=0
count_store_load=0
count_load_store=0
count_load_load=0
count_initializing=0

for ((i=1; i<=1000; i++)); do
    output=$(./run)
    if [[ $output == *"store-store detected"* ]]; then
        ((count_store_store++))
    fi
    if [[ $output == *"store-load detected"* ]]; then
        ((count_store_load++))
    fi
    if [[ $output == *"load-store detected"* ]]; then
        ((count_load_store++))
    fi
    if [[ $output == *"load-load detected"* ]]; then
        ((count_load_load++))
    fi
    ((count_initializing++))  # Always increment this counter
done

if [ $count_store_store -ne 0 ]; then
    echo "Count of 'store-store': $count_store_store"
elif [ $count_store_load -ne 0 ]; then
    echo "Count of 'store-load': $count_store_load"
elif [ $count_load_store -ne 0 ]; then
    echo "Count of 'load-store': $count_load_store"
elif [ $count_load_load -ne 0 ]; then
    echo "Count of load-load': $count_load_load"
fi

echo "Number of 'initializing' occurrences: $count_initializing"

