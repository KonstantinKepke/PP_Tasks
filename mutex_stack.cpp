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
    std::mutex m;
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

    void print_stack() { for(auto &el: v) { std::cout << el << std::endl;  } }
};

// thread_safe_stack::thread_safe_stack(/* args */){
// }

// thread_safe_stack::~thread_safe_stack(){
// }

//template<typename T>
// void writer(std::stop_token st, thread_safe_stack<T>& stack)
// {
//     Greeting G("Writer", 3);
//     int value=0;
//     while (!st.stop_requested() && value <34 )
//     {
//         std::cout << value++ << " " << std::endl;
//         std::cout << "push to stack \n";
//         stack.push_stack(value);
//         std::this_thread::sleep_for(200ms);      
//         value++;
//     }
//     std::cout << "\nstop req = " << st.stop_requested() << std::endl;

// }

template<typename T>
void writer(thread_safe_stack<T>& stack)
{
    Greeting G("Writer", 3);
    int value=0;
    while (value <34 )
    {
        std::cout << value++ << " " << std::endl;
        std::cout << "push to stack \n";
        stack.push_stack(value);
        std::this_thread::sleep_for(200ms);      
        value++;
    }
   
}

// template<typename T>
// void reader(std::stop_token st, thread_safe_stack<T>& stack)
// {
//     Greeting G("Reader", 5);
//     int value = 1;
//     while (!st.stop_requested() && value <34 )
//     {
//         std::cout << "get from to stack " << stack.pull_stack();
        
//         std::this_thread::sleep_for(200ms);      
//     }
//     std::cout << "\nstop req = " << st.stop_requested() << std::endl;

// }

int main(){
    Greeting G("try_lock_main()");

    thread_safe_stack<int> stack;
    for (int i=3; i<9; ++i){
        stack.push_stack(i);
    }
    stack.print_stack();

    int upper = stack.get_upper();
    std::cout << "upper = "<< upper << std::endl;
    std::cout << "upper = "<<  stack.get_upper() << std::endl;
    std::cout << "upper = "<<  stack.pull_stack() << std::endl;
    std::cout << "upper = "<<  stack.get_upper() << std::endl;
    // std::mutex m1, m2, m3;

    writer(&stack);
    //std::thread th1(&writer, stack);
    //std::thread th2(&reader, stack);
    
    // std::thread th3(&fCh, std::ref(m1), 'c');

    std::this_thread::sleep_for(300ms); //чтобы хотя бы один поток успел захватить мьютекс

    // while (m1.try_lock() == false) {
    //     std::this_thread::sleep_for(5ms); //чтобы хотя бы один поток успел захватить мьютекс
    //     std::cout << 'Q'; 
    // }

    // std::cout << std::endl<<"All mutexes captured!\n";

    // th1.join();
    // th2.join();
    // th3.join();
}