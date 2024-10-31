/**
 * Задан массив, например:
 const char* strings[] = { "Long-long ago..." ,"I am very sorry", "My Dog", …};

Требуется запустить количество потоков, равное числу строк в массиве.
Каждый поток должен выводить свой идентификатор и принимаемую строку, например:

 */

// !! Fix: remove alot of stop token to one in main(), and put it to all thread !!

#include "common_pp.hpp"

std::mutex m;

void threadFunc(std::stop_source& ss, string str, int i)
{
    ProgDeclare p("threadFunc " + str);

    while (!ss.get_token().stop_requested())
    {
        m.lock();
        cout << "th_Funk( " << i << " ) Pid =" << p.getPid() << "\t" << str << endl;
        m.unlock();
        std::this_thread::sleep_for(1000ms);
    }
}

int main()
{
    ProgDeclare p("Task 1_5 Thread = str");

    const char *strings[] = {"Long-long ago...", "I am very sorry", "My Dog", "1234", "ll", "11", "12"};

    u_int16_t num_str = std::size(strings);

    std::vector<std::jthread> v;

    std::stop_source ss;

    for (int i = 0; i < num_str; ++i)
    {
        std::jthread th1(threadFunc, std::ref(ss), strings[i], i);
        v.push_back(std::move(th1));
    }

    cout << "Press enter to exit" << endl;
    char ch = getchar();
    ss.request_stop();
    cout << "Just quit." << ch << endl;
}
