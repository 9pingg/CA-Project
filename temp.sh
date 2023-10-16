#!/bin/bash

# List of fruits
fruits=("Apple" "Banana" "Cherry" "Date" "Fig")
count_store_store=0
count_store_load=0
count_load_store=0
count_load_load=0
count_initializing=0

# Iterate through the list and print each fruit
for ((i=1; i<=1000; i++)); do
    output=$(./run)
    # echo "$output"
    if [[ $output == *"load-load detected"* ]]; then
        ((count_load_load++))
    fi
    if [[ $output == *"store-store detected"* ]]; then
        ((count_store_store++))
    fi
done

echo "Count of 'load-load': $count_load_load"
echo "Count of 'store-store': $count_store_store"
