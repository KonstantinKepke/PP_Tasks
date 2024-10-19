
//
// Method of class in thread
//

#include "include/common_pp.hpp"

void DrawMutex(char c) {
    static std::mutex m;
    m.lock();
    for (int i = 0; i < 20; i++) { std::cout << c; }
    m.unlock();
}

int main()
{
    Greeting G("Method of class in thread");

    std::thread t1(DrawMutex, 'A');
    std::thread t2(DrawMutex, 'B');
    std::thread t3(DrawMutex, 'C');
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
