/**
 * Задание - 8.а Требуется запустить несколько потоков, каждый из которых должен с заданным тайм-аутом (1 ms, 2 ms…) прибавлять полученное в качестве параметра (1,2,…) значение к общей сумме (вносить свою долю). В родительском потоке проверяем - как только значение суммы превысит заданный порог (например, 1000), все запущенные дочерние потоки требуется остановить. При этом каждый поток должен вывести диагностику: идентификатор потока и счетчик (сколько раз поток смог внести в общую сумму свою «добавку»).
    Подсказка: так как используются разделяемые данные, подумайте о «защите».
 */

#include "common_pp.hpp"
#include <random>

std::mutex m;

int NUM_THREADS = 3;

u_int32_t SUM_TO_STOP = 100;
u_int32_t current_sum = 0;

std::stop_source ss;

void threadFunc(std::stop_token st, int thread_num, int num_to_add, int timeout)
{
    ProgDeclare p("threadFunc " + std::to_string(++thread_num));
    int n = 1;

    std::stop_callback callBack(st, [&p, &n]() {
            std::cout << "CallBack works. thread # " <<  p.pid << ". Additions = " << n << ". current_sum =  " << current_sum << std::endl; });

// ?? optimized !!
    while (!st.stop_requested){
        m.lock();
        current_sum += num_to_add;
        m.unlock();
        n++;
        std::this_thread::sleep_for(std::chrono::milliseconds((timeout * 10)));
    }
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

    while (current_sum < SUM_TO_STOP)
    {
    }
    ss.request_stop();

    std::cout << "\nCurrent sum = " << current_sum << " Bye\n";
}
