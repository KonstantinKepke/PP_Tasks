#include "common_pp.hpp"

static bool running = {true};

std::counting_semaphore<1> sema(0);

// TBD ->2 sema

void pleer1(std::string &name)
{
    Greeting p("_" + name);
    std::this_thread::sleep_for(800ms); // time to pong started and wait ping on acqure()
    while (running)
    {
        cout << "PING " << endl;
        sema.release();
        std::this_thread::sleep_for(100ms);
    }
    sema.release();
}

void pleer2(std::string &name)
{
    Greeting p("_" + name);
    while (running)
    {
        if (sema.try_acquire())
        {
            // sema.acquire();
            cout << "pong  " << endl;
        }
        else
            cout << "pleer 2 dance! " << endl;
        std::this_thread::sleep_for(300ms);
    }
}

int main()
{
    Greeting p("ping-pong");

    std::vector<std::thread> v;
    std::string pl1 = "Pleer1";
    std::string pl2 = "Pleer2";

    std::jthread th1(pleer1, std::ref(pl1));
    std::jthread th2(pleer2, std::ref(pl2));

    cout << "Press enter to exit" << endl;
    char ch = getchar();
    cout << "Just quit." << ch << endl;
    running = false;
}
