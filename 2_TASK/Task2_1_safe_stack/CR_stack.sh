#!/bin/bash

set -x  # uncomment this line to debug (bash will print all commands it executes)

#file="main.cpp"

clear
echo -e  "rm -rf ./out/*"
rm -rf ./out/*

c++ --std=c++20 -o ./out/stack.bin -c stack.cpp 
c++ --std=c++20 -o ./out/ThreadSafeStack.bin -c ThreadSafeStack.cpp 

c++ --std=c++20 -o ./out/main.bin -c Task2_1_thread_stack.cpp 

c++ --std=c++20 -o ./out/task.bin ./out/stack.bin ./out/main.bin ./out/ThreadSafeStack.bin

./out/task.bin


