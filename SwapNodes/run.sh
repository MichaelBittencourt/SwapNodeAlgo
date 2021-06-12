#!/bin/bash

export OUTPUT_PATH="./output.txt"

for i in $(seq 1 5); do
    echo "Runing example $i:"
    cat input$i.txt | time -p ./a.out
    echo "Check if there diff"
    diff output.txt output$i.txt
done
