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
#include <string>

// docker build . -t clang_test:1
// docker run --rm  -it clang_test:1
#pragma once

using namespace std;

/**
 * decl prog name, start/end with work duration
 */
class ProgDeclare
{

    std::chrono::time_point<std::chrono::steady_clock> start, end;
    string prog_info;

public:
    pid_t pid;
    ProgDeclare(std::string Mess) : prog_info(Mess)
    {
        start = std::chrono::steady_clock::now();
#ifndef __APPLE__
        pid = gettid();
        cout << "Start _" << prog_info << "_ with pid = " << pid << std::endl;
#endif
    }
    int getPid() { return pid; };
    ~ProgDeclare()
    {
        end = std::chrono::steady_clock::now();
        std::chrono::duration<double /*,std::ratio<1,1>*/> elapsed = end - start;
        std::chrono::microseconds mc3 = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
#ifndef __APPLE__
        cout << "End _" << prog_info << "_ with pid = " << pid << " Duration: " << mc3.count() << " microseconds" << std::endl;
#else
        cout << "\nEnd _" << prog_info << " Duration: " << mc3.count() << " microseconds" << std::endl;
#endif
    }
};

class Greeting
{
    string greet;
    int offset = 0;
    std::chrono::time_point<std::chrono::steady_clock> start, end;

public:
    Greeting(string in) : greet(in)
    {
        std::cout << "Prog __" << greet << "__ started.\n";
        start = std::chrono::steady_clock::now();
    }
    Greeting(string in, int i) : greet(in), offset(i)
    {
        for (int j = 0; j < offset; ++j)
            std::cout << " ";
        std::cout << "Prog __" << greet << "__ started.\n";
        start = std::chrono::steady_clock::now();
    }
    ~Greeting()
    {
        end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::chrono::nanoseconds ns3 = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed);
        for (int j = 0; j < offset; ++j)
            std::cout << " ";
        std::cout << "Prog __" << greet << "__ END. \tDuration = " << ns3.count() << " nanoseconds" << std::endl;
    }
};
