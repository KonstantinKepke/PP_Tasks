#include "common_pp.hpp"

// !! FIX one semaphore -> two semaphores for true algorithm work

static bool running = {true};

void pleer(std::string &name, std::string &action, std::binary_semaphore &bs1, std::binary_semaphore &bs2, int &time)
{
    Greeting p(name);
    while (running)
    {
        if (bs1.try_acquire())
        {
            cout << action << endl;
            bs2.release();
        }
        else
        {
            cout << name << " Dance!" << endl;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(time));
    }
}

int main()
{
    Greeting p("ping-pong");

    std::vector<std::thread> v;
    std::string pl1 = "Pleer1";
    std::string pl2 = "\tPleer 2";
    std::string pl11 = "Ping";
    std::string pl22 = "\tPong";

    std::binary_semaphore sema1(true);
    std::binary_semaphore sema2(false);

    int t1 = 50;
    int t2 = 150;

    std::jthread th1(pleer, std::ref(pl1), std::ref(pl11), std::ref(sema1), std::ref(sema2), std::ref(t1));
    std::jthread th2(pleer, std::ref(pl2), std::ref(pl22), std::ref(sema2), std::ref(sema1), std::ref(t2));

    cout << "Press enter to exit" << endl;
    char ch = getchar();
    running = false;
    sema2.release();
    sema1.release();
    cout << "Just quit." << ch << endl;
}
