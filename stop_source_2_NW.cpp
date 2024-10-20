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
    Greeting G("KM");
    
    std::jthread th(f, 5); // prints 5 6 7 8... for approximately 3 seconds
    std::this_thread::sleep_for(1s);
    
    th.request_stop(); //OK

    std::this_thread::sleep_for(2s);
    return 0;
    
}