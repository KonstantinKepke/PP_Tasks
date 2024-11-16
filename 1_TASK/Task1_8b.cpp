/**
    8б. Задана сумма (например, 1000). Требуется запустить несколько потоков,
    каждый из которых должен с заданным тайм-аутом (например, 1 ms, 2 ms…)
    «забирать» из общей суммы свою долю, значение которой задается в качестве параметра (например, 1,2,…).
    Как только любой поток обнаруживает, что «деньги закончились», он завершает выполнение.
    При этом каждый поток должен вывести диагностику: идентификатор потока и сколько денег поток смог забрать из общей суммы.
 */

#include "common_pp.hpp"
#include <random>

std::mutex m;

int NUM_THREADS = 3;

int32_t BUDGET = 100;
int32_t current_sum = BUDGET;

std::stop_source ss;

void threadFunc(std::stop_token st, int thread_num, int num_to_sub, int timeout)
{
    ProgDeclare p("threadFunc " + std::to_string(++thread_num));
    int n = 1;
    int spent_all = 0;
    while (!st.stop_requested())
    {
        std::cout << "current summ : " << current_sum << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds((100)));
        m.lock();
        current_sum -= num_to_sub;
        if (current_sum > 0)
        {
            spent_all += num_to_sub;
        }
        else
        {
            ss.request_stop();
            std::cout << "FINAL STAT: " << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds((500)));
            m.unlock();
            break;
        }
        m.unlock();
        std::cout << "thread # " << thread_num << ". Deals = " << n++ << ". Spent all =  " << spent_all << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds((timeout * 10)));
    }
    std::cout << "FINAL STAT: thread # " << thread_num << ". Deals = " << n++ << ". Spent all =  " << spent_all << std::endl;
}

int main()
{
    ProgDeclare p("Task 1_8 ");

    std::vector<std::jthread> v;
    for (int n = 0; n < NUM_THREADS; ++n)
    {
        std::jthread th1(threadFunc, ss.get_token(), n, n + 2, n + 5);
        v.push_back(std::move(th1));
        std::this_thread::sleep_for(std::chrono::milliseconds((10)));
    }

    std::cout << "\nCurrent sum = " << current_sum << " Bye\n";
}
