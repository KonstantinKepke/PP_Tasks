#include <stdio.h>
#include <iostream>

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
//#include <tuple>
#include <iostream>
#include <fstream>
#include <filesystem>

#pragma once

using namespace std;

void ConvertFile (string file_in, string file_out);
string ApperLine(const string& line);

/**
 * decl prog name, start/end with work duration
 */
class ProgDeclare{

    std::chrono::time_point<std::chrono::steady_clock> start, end;
    string prog_info;
    pid_t pid;

public:
    ProgDeclare(std::string Mess):prog_info(Mess){
        start = std::chrono::steady_clock::now();
#ifndef __APPLE__
        pid = gettid();
        cout << "\nStart _"<< prog_info << "_ with pid = "<< pid <<std::endl;
#endif
    }
    ~ProgDeclare(){
        end = std::chrono::steady_clock::now();
        std::chrono::duration<double/*,std::ratio<1,1>*/> elapsed = end - start;
        std::chrono::microseconds mc3 = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
#ifndef __APPLE__
        cout << "\nEnd _"<< prog_info << "_ with pid = "<< pid << " Duration: " << mc3.count() << " microseconds" << std::endl;
#else
        cout << "\nEnd _"<< prog_info << " Duration: " << mc3.count() << " microseconds" << std::endl;
#endif
    }
};


void ConvertFile (string file_in, string file_out) {
   
#ifndef __APPLE__
    pid_t pid = gettid();
    cout << "\tThread № "<< pid <<", with "<< file_in << " and "<< file_out << "\tSTARTED!" << endl; 
#else
    cout << "\tThread № macos --- " << file_in << " and "<< file_out << "\tSTARTED!" << endl; 
#endif
    ifstream inputFile (file_in);
    ofstream outputFile (file_out);
    
    if (!inputFile.is_open() or !outputFile.is_open()) {
        cerr << "Error creating the file!" << endl;
        exit(1);
    }

    // string line; 
    // while (getline(inputFile, line)) {
    //     outputFile << ApperLine(line) << endl;
    // }
    // //std::transform(istreambuf_iterator<char> (inputFile), istreambuf_iterator<char> (), ostreambuf_iterator<char> (outputFile), std::toupper);
    //??
    std::transform(istreambuf_iterator<char> (inputFile), istreambuf_iterator<char> (inputFile), ostreambuf_iterator<char> (outputFile), std::toupper);

    inputFile.close();
    outputFile.close();
}

string ApperLine(const string& line){
    string ret_str;
    for (auto &ch : line) {
             //toupper(ch);
            ret_str += toupper(ch);
    }
    return ret_str;
}