
//
// try_lock_main()
//

#include "include/common_pp.hpp"
 
void writer_routine();

using namespace std::literals::chrono_literals;

template<typename T>
class thread_safe_stack
{
public:
    T i;
};

template<typename T>
void writer_routine()
{
    Greeting G("Writer", 3);
}

int main(){
    Greeting G("try_lock_main()");

    thread_safe_stack<int> stack_th;

    std::jthread th_writer(thread_safe_stack<int> &writer_routine);
    //th_writer.join();

}

 