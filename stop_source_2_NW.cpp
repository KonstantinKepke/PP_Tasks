//
// Working stop source with std::stop_source stop -> std::stop_token st=stop.get_token();
//

#include "include/common_pp.hpp"
 
using namespace std::literals::chrono_literals;
 
void f(std::stop_token st, int value)
{

    std::cout << "stop req = " << st.stop_requested() << std::endl;
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
    
    std::jthread th(f, 5); // prints 5 6 7 8... for approximately 3 seconds
    //st = th.get_stop_token();
    //std::cout << "Main stop req = " << st.stop_requested() << std::endl;
    std::this_thread::sleep_for(1s);
    
    th.request_stop();

    //std::cout << "Main stop req2 = " << st.stop_requested() << std::endl;
    std::this_thread::sleep_for(2s);
    
}