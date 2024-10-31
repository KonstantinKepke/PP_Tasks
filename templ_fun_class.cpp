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
void wr_int(T i)
{
    Greeting G("Wr INT", 3);   
    std:: cout << i << std::endl;
}

template<class T>
void writer_simple()
{
    Greeting G("Writer_simple", 3);   
//    std:: cout << stack_th.j << std::endl;
}


//template<class T>
void writer(thread_safe_stack<int>& stack_th)
{
   Greeting G("Writer", 3);   
    std:: cout << "Writer stack_th = " << ++stack_th.j << std::endl;
}

template<class T>
void writer_hard(T& stack_th)
{
   Greeting G("Writer HARD", 1);   
    std:: cout << "\t\tWriter_HARD stack_th = " << ++stack_th.j  << std::endl;
}

int main(){
    Greeting G("try_lock_main()");

    thread_safe_stack<int> stack_th;

    stack_th.j=19;
    int to_f = 9;
    std::thread th1 (&wr_int <decltype(to_f)>, std::ref(to_f));
    th1.join();

    std::thread th2 (&writer_simple <decltype(to_f)>);
    th2.join();

    std::thread th3 (&writer, std::ref(stack_th));
    th3.join();

    std::thread th4 (&writer_hard <decltype(stack_th)>, std::ref(stack_th));
    th4.join();


    std:: cout << "\t\tstack_th = " << stack_th.j  << std::endl;

    //writer(stack_th);

}