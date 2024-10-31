/**
 * 1.1. Запуск потоков с ожиданием завершения
 *   - 1.в Запускаем столько потоков, сколько ядер в системе
 */

#include "Task1.h"

#include <filesystem>
namespace fs = std::filesystem;

std::vector<std::string> in_files;
std::mutex m;

void thread_f(std::mutex &m, std::vector<std::string> &in_files)
{

    while (!in_files.empty())
    {
        std::string in, out, file;

        m.lock();
        file = in_files.back();
        in_files.pop_back();
        m.unlock();

        in = "./in_txt/" + file;
        out = "./out_txt/_" + file;
        ConvertFile(std::move(in), std::move(out));
    }
}

int main()
{
    ProgDeclare p("1_task - make files content uppercase. ");

    std::vector<std::thread> v;

    in_files.reserve(std::thread::hardware_concurrency());
    std::string path = "./in_txt/";
    for (auto &p : fs::directory_iterator(path))
    {
        in_files.push_back(p.path());
        in_files.back().erase(0, 9);
    }

    for (auto &el : in_files)
        std::cout << "in = " << el << std::endl;

    // 1.c Запускаем столько потоков, сколько ядер в системе
    // int processor_count = 3; // for example
    int processor_count = std::thread::hardware_concurrency();
    for (int i = 0; i < processor_count; ++i)
    {
        try
        {
            std::thread th1(thread_f, std::ref(m), std::ref(in_files));
            v.push_back(std::move(th1));
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    for (auto &el : v)
        el.join();
    v.clear();
}
