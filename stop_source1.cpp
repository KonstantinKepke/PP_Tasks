//
// Working stop source with std::stop_source stop -> std::stop_token st=stop.get_token();
//

#include "include/common_pp.hpp"
 
using namespace std::literals::chrono_literals;
 
void f(std::stop_source ss, int value)
{
    Greeting G("f()", 5);
    std::stop_token st=ss.get_token();

    std::cout << "stop req = " << st.stop_requested() << std::endl;
    while (!st.stop_requested() && value <34 )
    {
        std::cout << value++ << " +" << std::flush;
        std::this_thread::sleep_for(200ms);      
    }
    std::cout << "\nstop req = " << st.stop_requested() << std::endl;
}
 
 // ?? if we don't pass std::stop_token or std::stop_state so we couldn't process and get stop token insside threads
void f2( std::stop_token st, int value)
{
    Greeting G("f2()", 10);  
    std::cout << "F2 stop req = " << st.stop_requested() << std::endl;
    while (!st.stop_requested() && value <34 )
    {
        std::cout << value++ << " +" << std::flush;
        std::this_thread::sleep_for(200ms);      
    }
    std::cout << "\nstop req = " << st.stop_requested() << std::endl;
}
 
int main()
{
    Greeting G("KJH");
    // case 1 We pull stop_source stop which contains stop_token and 
    //          and get stop_token from f() from stop_source 
    // for stop f() we set stop_source stop.request_stop();
    std::stop_source stop;
    //std::stop_token st=stop.get_token(); // we can print it before and after
   
    std::jthread th(f, stop, 5); // prints 5 6 7 8... for approximately 3 seconds
    std::this_thread::sleep_for(2s);
    
    stop.request_stop();

    // case 2 ==================
    std::this_thread::sleep_for(1s);
    std::jthread th2(f2, 5); // prints 5 6 7 8... for approximately 3 seconds
    std::this_thread::sleep_for(2s);
   
}