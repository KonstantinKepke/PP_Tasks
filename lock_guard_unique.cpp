
//
// try_lock_main()
//

#include "include/common_pp.hpp"
 
using namespace std::literals::chrono_literals;


void writer_LG(string name, std::mutex& m)
{
    Greeting G("WRITER.."+ name, 3);
    int value=0;
    
    while (value <11 )
    {
        {   
            std::lock_guard<std::mutex> lg(m);
            std::cout << name << " val= "<< value<< "\n";
        }
        std::this_thread::sleep_for(100ms);
        value++;
    }
}

void writer_UL(string name, std::mutex& m)
{
    Greeting G("WRITER.."+ name, 3);
    int value=0;
    
    while (value <11 )
    {
        {   
            std::unique_lock<std::mutex> ul(m);
            std::cout << name << " val= "<< value<< "\n";
        }
        std::this_thread::sleep_for(100ms);
        value++;
    }
}

int main(){
    Greeting G("MUTEX STACK");

    std::mutex m;
    
    std::thread th_writer1(&writer_UL, " FIRST", std::ref(m));
    std::thread th_writer2(&writer_UL, " second", std::ref(m));
    //std::thread th_writer2(&writer, " second");
    
    th_writer1.join();
    th_writer2.join();

}

 