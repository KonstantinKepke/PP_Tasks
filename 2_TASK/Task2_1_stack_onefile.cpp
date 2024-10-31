
//
// Task 2_1.  Потокобезопасный стек. std::mutex. std::lock_guard. std::shared_mutex. std::lock(). std::scoped_lock. 
//

#include "../include/common_pp.hpp"

//std::vector<std::exception_ptr> g_exceptions;

#define STACK_NUM 15

using namespace std::literals::chrono_literals;


class ThreadSafeStack
{
private:
    std::vector<int> v;
    std::mutex m;
    static int numOfStack;
    const int stackID = numOfStack;

public:

    ThreadSafeStack ()
    {
        numOfStack++;
        std::cout <<" Cstr() ThreadSafeStack ID = " << stackID << std::endl;
    };


    ThreadSafeStack (const ThreadSafeStack& tSS) 
    {
        m.lock();
        std::copy(tSS.v.begin(), tSS.v.end(), v.begin());
        numOfStack++;
        std::cout <<" copy csrt(& tSS) ThreadSafeStack ID = " << stackID << std::endl;
        m.unlock();
    };

    ThreadSafeStack (ThreadSafeStack& tSS) 
    {
        m.lock();
        std::copy(tSS.v.begin(), tSS.v.end(), v.begin());
        numOfStack++;
        std::cout <<" copy csrt(& tSS) ThreadSafeStack ID = " << stackID << std::endl;
        m.unlock();
    };

    ThreadSafeStack operator=(ThreadSafeStack& tSS)
    {
        ThreadSafeStack temp;
        m.lock();
        std::copy(tSS.v.begin(), tSS.v.end(), temp.v.begin());
        numOfStack++;
        std::cout <<" copy(=) csrt(& tSS) ThreadSafeStack ID = " << stackID << std::endl;
        m.unlock();
        return temp;
    };

    ~ThreadSafeStack ()
    {
        std::cout <<" DSTR() ThreadSafeStack ID = " << stackID << std::endl;
    };

    void printStackId () 
    {
        std::cout <<"\t\t\t\tThreadSafeStack ID = " << stackID << std::endl;
    };

    int push_stack(int el, string name)
    {
        m.lock();
        v.push_back(el);
        m.unlock();
        std::cout << name << " -> a psh: \t";
        print_stack();
        return v.size();
    };
   
// copy constr + destr  - TBD

// optional - tyi

    // получение значения последнего элемента - T& back();
    // и удаление последнего элемента – void pop_back();
    // COMBINE .back() and pop_back() under one mutex
    int pull_stack(string name)
    {
        m.lock();
        int el = v.back();
        v.pop_back();
        m.unlock();
        std::cout << name << "-> b pop: \t";
        print_stack();
        return el;
    };

    bool empty() // const !!
    {
        m.lock();
        bool res = v.empty();
        m.unlock();
        return res;
    }

    int get_upper() const
    { 
        return v.back(); 
    }

    void print_stack() const
    {
        std::cout << "Stack Id = " << stackID << ".\t";
        for (auto &el : v)
        {
            std::cout << el << "\t";
        }
        std::cout << " \n";
    }
};

int ThreadSafeStack::numOfStack = 1;

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

int main()
{
    Greeting G("MUTEX STACK");

    ThreadSafeStack stack_th1;
    stack_th1.printStackId();

    ThreadSafeStack stack_th2(stack_th1);
    stack_th2.printStackId();

    ThreadSafeStack stack_th3(stack_th2);
    stack_th3.printStackId();

    ThreadSafeStack stack_th4 = stack_th1;
    stack_th4.printStackId();

    //stack_th.print_stack();

    // std::thread th_writer1(&writer, std::ref(stack_th), "Wr1");

    // std::thread th_reader1(&reader, std::ref(stack_th), "Rdr1");
    // // std::thread th_writer2(&writer, std::ref(stack_th), "Wr2");
    // std::thread th_reader2(&reader, std::ref(stack_th), "Rdr2");

    // th_writer1.join();
    // // th_writer2.join();
    // th_reader1.join();

    // th_reader2.join();

  //  stack_th.print_stack();
}
