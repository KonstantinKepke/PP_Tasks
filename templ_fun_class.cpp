//
// try_lock_main()
//

#include "include/common_pp.hpp"
 
using namespace std::literals::chrono_literals;


template<class T>
class thread_safe_stack
{
private:
    T i;
public:
    T j;
};

template<class T>
void writer(thread_safe_stack<T>& stack_th)
{
    Greeting G("Writer", 3);   
    std:: cout << stack_th.j << std::endl;
}

template<class T>
void wr_int(int& i)
{
    Greeting G("Wr INT", 3);   
    std:: cout << i << std::endl;
}


int main(){
    Greeting G("try_lock_main()");

    thread_safe_stack<int> stack_th;

    int to_f = 9;
    std::thread th1 (&wr_int <decltype(&to_f)>, std::ref(to_f));
    th1.join();
    writer(stack_th);

}