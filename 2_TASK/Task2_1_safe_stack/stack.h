#include "common_pp.hpp"

using namespace std::literals::chrono_literals;

#define STACK_NUM 15

class ThreadSafeStack
{
private:
    std::vector<int> v;
    std::mutex m;
    static int numOfStack;
    const int stackID = numOfStack;

public:
    ThreadSafeStack()
    {
        numOfStack++;
        std::cout << " Cstr() ThreadSafeStack ID = " << stackID << std::endl;
    };

    // ThreadSafeStack (const ThreadSafeStack& tSS)
    // {
    //     m.lock();
    //     std::copy(tSS.v.begin(), tSS.v.end(), v.begin());
    //     numOfStack++;
    //     std::cout <<" copy csrt(& tSS) ThreadSafeStack ID = " << stackID << std::endl;
    //     m.unlock();
    // };

    ThreadSafeStack(ThreadSafeStack &tSS);

//    ThreadSafeStack operator=(ThreadSafeStack &tSS)
    ThreadSafeStack operator=(ThreadSafeStack &tSS)
    {
        ThreadSafeStack temp;
        m.lock();
        std::copy(tSS.v.begin(), tSS.v.end(), temp.v.begin());
        numOfStack++;
        std::cout << " copy(=) csrt(& tSS) ThreadSafeStack ID = " << stackID << std::endl;
        m.unlock();
        return temp;
    };


    ~ThreadSafeStack();
    void printStackId();
    int push_stack(int el, string name);

    // copy constr + destr  - TBD

    // optional - tyi
    // получение значения последнего элемента - T& back();
    // и удаление последнего элемента – void pop_back();
    // COMBINE .back() and pop_back() under one mutex
    int pull_stack(string name);
    bool empty();
    int get_upper() const;
    void print_stack() const;
};

void writer(ThreadSafeStack &, string);
void reader(ThreadSafeStack &, string);