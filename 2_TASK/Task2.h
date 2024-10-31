#include <stdio.h>
#include <iostream>

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
// #include <tuple>
#include <iostream>
#include <fstream>
#include <filesystem>

#pragma once

using namespace std;

string ApperLine(const string &line);

/**
 * decl prog name, start/end with work duration
 */
class ProgDeclare
{

    std::chrono::time_point<std::chrono::steady_clock> start, end;
    string prog_info;
    pid_t pid;

public:
    ProgDeclare(std::string Mess) : prog_info(Mess)
    {
        start = std::chrono::steady_clock::now();
#ifndef __APPLE__
        pid = gettid();
        cout << "\nStart _" << prog_info << "_ with pid = " << pid << std::endl;
#endif
    }
    ~ProgDeclare()
    {
        end = std::chrono::steady_clock::now();
        std::chrono::duration<double /*,std::ratio<1,1>*/> elapsed = end - start;
        std::chrono::microseconds mc3 = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
#ifndef __APPLE__
        cout << "\nEnd _" << prog_info << "_ with pid = " << pid << " Duration: " << mc3.count() << " microseconds" << std::endl;
#else
        cout << "\nEnd _" << prog_info << " Duration: " << mc3.count() << " microseconds" << std::endl;
#endif
    }
};
