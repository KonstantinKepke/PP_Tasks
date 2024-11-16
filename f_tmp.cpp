
//
// try_lock_main()
//

#include "include/common_pp.hpp"
 
using namespace std::literals::chrono_literals;



void F()
{
    if(false) {
        std::cout << "f() true" << std::endl;
        return;
    }
    else {
        std::cout << "f() false " << std::endl;
        return;
    }
}

int main(){
    Greeting G("F()");

    F();

    return 0;
}

 