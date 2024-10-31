#include "common_pp.hpp"
#include "stack.h"

int ThreadSafeStack::numOfStack = 1;

class ThreadSafeStack;


void writer(ThreadSafeStack &stack_th, string name)
{
    Greeting G("WRITER.." + name, 3);

    int value = 0;
    while (value < STACK_NUM)
    {
        // std::cout << value<< "\t";
        stack_th.push_stack(value, name);
        value++;
        std::this_thread::sleep_for(100ms);
    }
}

void reader(ThreadSafeStack &stack_th, string name)
{
    Greeting G("Reader.." + name, 3);
    while (!stack_th.empty())
    {
        // std::cout << stack_th.pull_stack() <<  "\t";
        stack_th.pull_stack(name);
        std::this_thread::sleep_for(200ms);
    }
}
