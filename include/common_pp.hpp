#include <stdio.h>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cctype>

#pragma once

using namespace std;

class Greeting {
    string greet;
    std::chrono::time_point<std::chrono::steady_clock> start, end;
public:    
    Greeting(string in) : greet(in) { 
        std::cout << "Prog __" << greet << "__ started.\n";
        start = std::chrono::steady_clock::now();
    }
    ~Greeting(){ 
        end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::chrono::nanoseconds ns3 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed);
        std::cout << "\nProg __" << greet << "__ END. \tDuration = " << ns3.count() << " nanoseconds" << std::endl;
    }
};