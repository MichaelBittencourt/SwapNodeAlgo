#!/bin/bash

export OUTPUT_PATH="./output.txt"

for i in $(seq 1 4); do
    cat input$i.txt | ./a.out
    diff output.txt output$i.txt
done
