/**
 * 1.1. Запуск потоков с ожиданием завершения
 *   - 1.а Последовательно запускаем потоки. Очередной поток запускаем только после завершения текущего  Измерьте время работы фрагмента.
 */

#include "Task1.h"

#include <filesystem>
namespace fs = std::filesystem;

int main() {
    ProgDeclare p("1_task - make files content uppercase");
       
    std::vector<std::thread> v;
    string in, out;
    
    std::vector<std::string> in_files;
    in_files.reserve( std::thread::hardware_concurrency());
    std::string path = "./in_txt/";
    for (auto & p : fs::directory_iterator(path)){
        in_files.push_back(p.path());
        in_files.back().erase(0,9);
    }
     
    for (auto & el : in_files) std::cout << "in = " << el << std::endl;

// 1.а Последовательно запускаем потоки. Очередной поток запускаем только после завершения текущего
    {   
        ProgDeclare p("1.a");
        for (auto &el: in_files){
            in = path + el;
            out = "./out_txt/" + el;
            std::thread th1(ConvertFile, std::ref(in), std::ref(out));
            th1.join();
        }
    }
}
