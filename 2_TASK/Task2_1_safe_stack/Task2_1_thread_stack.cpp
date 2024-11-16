
//
// Task 2_1.  Потокобезопасный стек. std::mutex. std::lock_guard. std::shared_mutex. std::lock(). std::scoped_lock. 
//

#include "stack.h"

std::vector<std::exception_ptr> g_exceptions;


int main()
{
    Greeting G("MUTEX STACK");

    ThreadSafeStack stack_th1;
    stack_th1.printStackId();

    ThreadSafeStack stack_th2;
    stack_th2 = stack_th1;
    stack_th2.printStackId();

    // ThreadSafeStack stack_th3(stack_th2);
    // stack_th3.printStackId();

    // ThreadSafeStack stack_th4 = stack_th1;
    // stack_th4.printStackId();

    //stack_th.print_stack();

    // std::thread th_writer1(&writer, std::ref(stack_th1), "Wr1");

    // std::thread th_reader1(&reader, std::ref(stack_th1), "Rdr1");
    // // std::thread th_writer2(&writer, std::ref(stack_th), "Wr2");
    // std::thread th_reader2(&reader, std::ref(stack_th1), "Rdr2");

    // th_writer1.join();
    // // th_writer2.join();
    // th_reader1.join();

    // th_reader2.join();

    //stack_th1.print_stack();
}
