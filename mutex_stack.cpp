
//
// try_lock_main()
//

#include "include/common_pp.hpp"
 
using namespace std::literals::chrono_literals;

template<typename T>
class thread_safe_stack
{
private:
    std::vector<T> v;
    //std::mutex m;
public:
    // thread_safe_stack(/* args */);
    // ~thread_safe_stack();
    int push_stack(T el){
        v.push_back(el);
        return v.size();
    };

    T pull_stack(){
        T el=v.back();
        v.pop_back();
        return el;
    };

    bool empty(){ return v.empty(); }

    T get_upper(){ return v.back(); }

    void print_stack() { std::cout << "Stack: \t"; for(auto &el: v) { std::cout << el << "\t";  }  std::cout << " End stack\n";}
};

template<typename T>
void writer(thread_safe_stack<T>& stack_th)
{
    std::cout<< "WRITER..";
    Greeting G("Writer", 3);
    int value=0;
    while (value <8 )
    {
        std::cout << "push: " << value << "\t";
        stack_th.push_stack(value);
        value++;
        std::this_thread::sleep_for(200ms); 
    }
}

template<typename T>
void reader(thread_safe_stack<T>& stack_th)
{
    Greeting G("Reader", 3);
    while (!stack_th.empty() )
    {
        std::cout << stack_th.pull_stack() <<  "\t";
        std::this_thread::sleep_for(200ms); 
    }
}

int main(){
    Greeting G("MUTEX STACK");

    thread_safe_stack<int> stack_th;

    stack_th.print_stack();

    std::jthread th_writer(thread_safe_stack<int> &writer, thread_safe_stack<int> stack_th);
    //writer(stack_th);


    stack_th.print_stack();

    //th_writer.join();
    //reader(stack_th);
    //stack_th.print_stack();
}

 