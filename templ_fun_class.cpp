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

int main(){
    Greeting G("try_lock_main()");

    thread_safe_stack<int> stack_th;
    writer(stack_th);

}