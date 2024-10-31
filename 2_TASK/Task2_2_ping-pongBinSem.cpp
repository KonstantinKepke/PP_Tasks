#include "common_pp.hpp"

static bool running = {true};

std::binary_semaphore sema1(true);
std::binary_semaphore sema2(false);

void pleer1()
{
    Greeting p("Pleer 1");
    // sema1.release();
    std::this_thread::sleep_for(1000ms);
    while (running)
    {
        if (sema1.try_acquire())
        {
            cout << "PING  " << endl;
            sema2.release();
        }
        else
        {
            //cout << "pleer 1 dance! " << endl;
        }
        std::this_thread::sleep_for(150ms);
    }
}

void pleer2()
{
    Greeting p("Pleer 2");
    while (running)
    {
        if (sema2.try_acquire())
        {
            cout << "\tpong  " << endl;
            sema1.release();
        }
        else
        {
            cout << "\t\tpleer 2 dance! " << endl;
        }
        std::this_thread::sleep_for(50ms);
    }
}

int main()
{
    Greeting p("ping-pong");

    std::vector<std::thread> v;
    std::string pl1 = "Pleer1";
    std::string pl2 = "Pleer2";

    std::jthread th1(pleer1);
    std::jthread th2(pleer2);

    cout << "Press enter to exit" << endl;
    char ch = getchar();
    running = false;
    sema2.release();
    sema1.release();
    cout << "Just quit." << ch << endl;
}
