#!/bin/bash

#set -x  # uncomment this line to debug (bash will print all commands it executes)

#file="main.cpp"

if [ $# -eq 0 ] ; then
    echo "Usage: $0 [tasc_to_compile_and_run.cpp]"
    exit 1
else
    echo "Input param=$1"
    #file=( $( $1 | sed "s/.cpp//g")) ;
    file="${1%.*}"
    file="./out/$file.bin"
fi
echo -e "Try to make bin $file"
c++ --std=c++20 -o $file $1 -O0
if [ $? -eq 0 ] ; then
    echo -e "\033[92mMaking Build successfully - $file. Starting: \033[37m\n";
    $file
else
    echo -e "\033[31mMaking Build - Error.\033[37m\n";
    exit 1
fi

