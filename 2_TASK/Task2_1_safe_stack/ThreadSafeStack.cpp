#include "stack.h"

ThreadSafeStack::ThreadSafeStack(ThreadSafeStack &tSS)
{
    m.lock();
    std::copy(tSS.v.begin(), tSS.v.end(), v.begin());
    numOfStack++;
    std::cout << " copy csrt(& tSS) ThreadSafeStack ID = " << stackID << std::endl;
    m.unlock();
};

// ThreadSafeStack operator=(ThreadSafeStack &tSS)
// {
//     ThreadSafeStack temp;
//     m.lock();
//     std::copy(tSS.v.begin(), tSS.v.end(), temp.v.begin());
//     numOfStack++;
//     std::cout << " copy(=) csrt(& tSS) ThreadSafeStack ID = " << stackID << std::endl;
//     m.unlock();
//     return temp;
// };

ThreadSafeStack::~ThreadSafeStack()
{
    std::cout << " DSTR() ThreadSafeStack ID = " << stackID << std::endl;
};

void ThreadSafeStack::printStackId()
{
    std::cout << "\t\t\t\tThreadSafeStack ID = " << stackID << std::endl;
};

int ThreadSafeStack::push_stack(int el, string name)
{
    m.lock();
    v.push_back(el);
    m.unlock();
    std::cout << name << " -> a psh: \t";
    print_stack();
    return v.size();
};

int ThreadSafeStack::pull_stack(string name)
{
    m.lock();
    int el = v.back();
    v.pop_back();
    m.unlock();
    std::cout << name << "-> b pop: \t";
    print_stack();
    return el;
};

bool ThreadSafeStack::empty()
{
    m.lock();
    bool res = v.empty();
    m.unlock();
    return res;
}

void ThreadSafeStack::print_stack() const
{
    std::cout << "Stack Id = " << stackID << ".\t";
    for (auto &el : v)
    {
        std::cout << el << "\t";
    }
    std::cout << " \n";
}

int ThreadSafeStack::get_upper() const
{
    return v.back();
}
