#include <iostream>
#include <thread>

#include "common_pp.hpp"
 
using namespace std::literals::chrono_literals;
 
void f(std::stop_source ss, int value)
{

    std::stop_token st=ss.get_token();

    std::cout << "s r = " << st.stop_requested() << std::endl;
    while (!st.stop_requested() && value <34 )
    {
        std::cout << value++ << " +" << std::flush;
        std::this_thread::sleep_for(200ms);      
    }
    std::cout << "\n stop req = true" << std::endl;
    std::cout << "s r = " << st.stop_requested() << std::endl;
}
 
int main()
{

    Greeting G("KJH");
    if ( 0 == 0) {}
    std::stop_source stop;
    std::stop_token st=stop.get_token();
   
    std::jthread th(f, stop, 5); // prints 5 6 7 8... for approximately 3 seconds
    std::this_thread::sleep_for(1s);
    
    stop.request_stop();
    std::this_thread::sleep_for(2s);
    
}