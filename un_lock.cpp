#include "include/common_pp.hpp"
 
using namespace std::literals::chrono_literals;

struct Box {
    explicit Box(int num) : num_things{num} {}
 
    int num_things;
    std::mutex m;
};
 
void swap_2(Box &from, Box &to, string name)
{
    Greeting G("Transfer"+name);
    // на самом деле пока не блокирует
    std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
    std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);
 
    // блокирует оба объекта unique_lock без взаимной блокировки
    std::this_thread::sleep_for(300ms);
    std::lock(lock1, lock2);
 
    int tmp= from.num_things;
    from.num_things = to.num_things;
    to.num_things = tmp;
     
    std::cout << "thread "+name << " from.num_things = " << from.num_things <<std::endl;
    std::cout << "thread "+name << " to.num_things = " << to.num_things <<std::endl;

    
    from.m.unlock();
    to.m.unlock();
    // мьютексы 'from.m' и 'to.m' разблокируются в деструкторах 'unique_lock'
}

void inc_b(Box &b, string name){

    for (int j=0; j<10; j++){
        b.num_things++;
        std::cout << "thread "+name << "  = " << b.num_things <<std::endl;
        std::this_thread::sleep_for(100ms);
    }
    
}

 
int main()
{
    Greeting G("UNIQUE LOCK from https://radioprog.ru/post/1405");
    Box acc1(100);
    Box acc2(50);
 
    std::thread t1(&swap_2, std::ref(acc1), std::ref(acc2), "A");
    //std::thread t2(&swap_2, std::ref(acc2), std::ref(acc1), "B");
    std::thread t3(&inc_b, std::ref(acc2), "T1");
    std::thread t4(&inc_b, std::ref(acc1), "T2");
 
    t1.join();
//    t2.join();
    t3.join();
    t4.join();
}