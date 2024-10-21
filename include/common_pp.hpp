#include <stdio.h>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cctype>
#include <mutex>
#include <semaphore>

#pragma once

using namespace std;

class Greeting {
    string greet;
    int offset=0;
    std::chrono::time_point<std::chrono::steady_clock> start, end;
public:    
    Greeting(string in) : greet(in) { 
        std::cout << "Prog __" << greet << "__ started.\n";
        start = std::chrono::steady_clock::now();
    }
    Greeting(string in, int i) : greet(in), offset(i){ 
        for(int j=0;j< offset;++j) std::cout << " ";
        std::cout << "Prog __" << greet << "__ started.\n";
        start = std::chrono::steady_clock::now();
    }
    ~Greeting(){ 
        end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::chrono::nanoseconds ns3 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed);
        for(int j=0;j< offset;++j) std::cout << " ";
        std::cout << "Prog __" << greet << "__ END. \tDuration = " << ns3.count() << " nanoseconds" << std::endl;
    }
};