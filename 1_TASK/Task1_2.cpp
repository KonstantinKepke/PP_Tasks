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
    // for (auto & el : in_files) std::cout << "in = " << el << std::endl;

// 1.б Запускаем столько потоков, сколько файлов требуется обработать

    {   
        ProgDeclare p("1.b");
        for (auto &el: in_files){
            in = "./in_txt/"+ el;
            out = "./out_txt/_"+ el;
            std::thread th1(ConvertFile, std::move(in), std::move(out));
            v.push_back(std::move(th1));
        }
        for (auto &el: v) el.join();
        v.clear();
    }
}

// make 128 files
// std::filesystem::copy_options my_options;
// my_options = std::filesystem::copy_options::overwrite_existing;
// in = "./in_txt/1.txt" ;
// std::vector<std::string> names;
