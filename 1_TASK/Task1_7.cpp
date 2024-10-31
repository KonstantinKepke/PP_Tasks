/**
 * Задание 7. Класс jthread. mutex Пустой вектор. Потоки параллельно добавляют каждый свое значение. Как только сумма превысит заданное значение, все потоки должны завершиться!
 */

#include "common_pp.hpp"
#include <random>

std::mutex m;

int NUM_THREADS = 10;
u_int32_t SUM_TO_STOP = 340;
u_int32_t current_sum = 0;

std::vector<u_int32_t> nums;
std::stop_source ss;

void threadFunc(std::stop_token st, int thread_num)
{
    ProgDeclare p("threadFunc " + std::to_string(++thread_num));

    while (!st.stop_requested())
    {

 //       MORE FAST but in vector may adds several nums after  current_sum > SUM_TO_STOP
 //       reason, that other threads wait on mutex, and after add number to stack before check rule
        // m.lock();
        //     nums.push_back(thread_num);
        //     current_sum += thread_num;
        // m.unlock();
        // if( current_sum > SUM_TO_STOP ) {
        //     //nums.pop_back();
        //     ss.request_stop();
        // }


//???? optimize!!
        m.lock();
        if (current_sum >= SUM_TO_STOP)
        {
            ss.request_stop();
        }
        else
        {
            nums.push_back(thread_num);
            current_sum += thread_num;
        }
        m.unlock();
        std::this_thread::sleep_for(10ms);
    }
}

int main()
{
    ProgDeclare p("Task 1_7 Vector sum");

    // std::random_device rd; // obtain a random number from hardware
    // std::mt19937 gen(rd()); // seed the generator
    // std::uniform_int_distribution<> distr(25, 63); // define the range

    std::vector<std::jthread> v;
    for (int n = 0; n < NUM_THREADS; ++n)
    {
        std::jthread th1(threadFunc, ss.get_token(), n);
        v.push_back(std::move(th1));
    }

    for (auto &el : v)
        el.join();

    std::cout << "\n\nWe've got numbers in vector = " << current_sum << ". SUM_TO_STOP = " << SUM_TO_STOP << "\t vector = ";
    for (auto &el : nums)
    {
        std::cout << el << " ";
    }
    std::cout << "\nBye";
}
