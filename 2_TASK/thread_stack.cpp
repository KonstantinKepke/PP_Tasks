
//
// thread_stack
//

#include "Task2.h"
#include "../include/common_pp.hpp"
 
using namespace std::literals::chrono_literals;

class thread_safe_stack
{
private:
    std::vector<int> v;
    std::mutex m;
public:
    int push_stack(int el, string name){
        m.lock();
        v.push_back(el);
        std::cout << name << " -> a psh: \t";    print_stack();
        m.unlock();
        return v.size();
    };

    int pull_stack(string name){
        m.lock();
        int el=v.back();
        std::cout << name << "-> b pop: \t";     print_stack();
        v.pop_back();
        m.unlock();
        return el;
    };

    bool empty(){ 
        m.lock();
        bool res=v.empty();
        m.unlock();
        return v.empty(); 
    }
    int get_upper(){ return v.back(); }
    void print_stack() { std::cout << "Stack: \t"; for(auto &el: v) { std::cout << el << "\t";  }  std::cout << " \n";}
};


void writer(thread_safe_stack& stack_th, string name)
{
    Greeting G("WRITER.."+name, 3);

    fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
             "Hello, {}!\n", "world");
    int value=0;
    while (value <11 )
    {
        //std::cout << value<< "\t";
        stack_th.push_stack(value, name);
        value++;
        std::this_thread::sleep_for(100ms); 
    }
}

void reader(thread_safe_stack& stack_th, string name)
{
    Greeting G("Reader.."+name, 3);
    while (!stack_th.empty() )
    {
        //std::cout << stack_th.pull_stack() <<  "\t";
        stack_th.pull_stack(name);
        std::this_thread::sleep_for(200ms); 
    }
}

int main(){
    Greeting G("MUTEX STACK");

    thread_safe_stack stack_th;

    stack_th.print_stack();

    std::thread th_writer1(&writer, std::ref(stack_th), "Wr1");
    std::thread th_reader1(&reader, std::ref(stack_th), "Rdr1");
    //std::thread th_writer2(&writer, std::ref(stack_th), "Wr2");
    std::thread th_reader2(&reader, std::ref(stack_th), "Rdr2");

    th_writer1.join();
    //th_writer2.join();
    th_reader1.join();
   
    th_reader2.join();

    stack_th.print_stack();
}

 