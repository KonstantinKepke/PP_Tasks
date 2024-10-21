#include "include/common_pp.hpp"
 
using namespace std::literals::chrono_literals;

std::counting_semaphore<1> sema(0);

struct Box {
    explicit Box(int num) : num_things{num} {}
 
    int num_things;
};

void f1(char ch){

}
 
int main()
{
    Greeting G("SEMA");

    Box acc1(100);
    Box acc2(50);
 
    std::vector<int> v;
    

    std::thread t1(&f1, 'A');
    // //std::thread t2(&swap_2, std::ref(acc2), std::ref(acc1), "B");
    // std::thread t3(&inc_b, std::ref(acc2), "T1");
    // std::thread t4(&inc_b, std::ref(acc1), "T2");
 
//     t1.join();
// //    t2.join();
//     t3.join();
//     t4.join();
}