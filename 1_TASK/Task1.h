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
        pid = gettid();
        cout << "\nStart _"<< prog_info << "_ with pid = "<< pid <<std::endl;
    }
    ~ProgDeclare(){
        end = std::chrono::steady_clock::now();
        std::chrono::duration<double/*,std::ratio<1,1>*/> elapsed = end - start;
        std::chrono::microseconds mc3 = std::chrono::duration_cast<std::chrono::microseconds>(elapsed);
        cout << "\nEnd _"<< prog_info << "_ with pid = "<< pid << " Duration: " << mc3.count() << " microseconds" << std::endl;
    }
};


void ConvertFile (string file_in, string file_out) {
   
    pid_t pid = gettid();
    cout << "\tThread № "<< pid <<", with "<< file_in << " and "<< file_out << "\tSTARTED!" << endl; 
    
    ifstream inputFile (file_in);
    ofstream outputFile (file_out);
    
    if (!inputFile.is_open() or !outputFile.is_open()) {
        cerr << "Error creating the file!" << endl;
        exit(1);
    }
    string line; 
    while (getline(inputFile, line)) {
        outputFile << ApperLine(line) << endl;
    }
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