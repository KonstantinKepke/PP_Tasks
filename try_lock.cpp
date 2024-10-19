//
// try_lock_main()
//

#include "include/common_pp.hpp"
 
using namespace std::literals::chrono_literals;
 
void fCh(std::mutex& m, char c){
    m.lock();
    for (size_t i = 0; i < 10; i++) { 
        std::cout << c; 
        std::this_thread::sleep_for(5ms); //чтобы хотя бы один поток успел захватить мьютекс
    }
    m.unlock();
}
 
 int main(){
    Greeting G("try_lock_main()");

    std::mutex m1, m2, m3;

    // std::thread th1(&fCh, std::ref(m1), 'A');
    // std::thread th2(&fCh, std::ref(m2), 'B');
    // std::thread th3(&fCh, std::ref(m3), 'c');
    std::thread th1(&fCh, std::ref(m1), 'A');
    std::thread th2(&fCh, std::ref(m1), 'B');
    std::thread th3(&fCh, std::ref(m1), 'c');

    std::this_thread::sleep_for(5ms); //чтобы хотя бы один поток успел захватить мьютекс

    while (m1.try_lock() == false) {
        std::this_thread::sleep_for(5ms); //чтобы хотя бы один поток успел захватить мьютекс
        std::cout << 'Q'; 
    }

    std::cout << std::endl<<"All mutexes captured!\n";

  //  m1.unlock(); m2.unlock(); m3.unlock();

    // th1.detach(); th2.detach(); th3.detach();
    th1.join();
    th2.join();
    th3.join();
}