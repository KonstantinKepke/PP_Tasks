#include "common_pp.hpp"

#define INEER_STOP_TOKEN

std::counting_semaphore<1> sema(0);

void pleer1 (std::stop_token st, std::string& name){
    Greeting p("_"+name);
    std::this_thread::sleep_for(800ms); // time to pong started and wait ping on acqure()
    while (!st.stop_requested()){
        cout << "PING "<< endl;
        sema.release();
        std::this_thread::sleep_for(1500ms);
    }
    sema.release();
}

void pleer2 (std::stop_token st, std::string& name){
    Greeting p("_"+name);
    while (!st.stop_requested()){       
        if (sema.try_acquire())
        {
            //sema.acquire();
            cout << "pong  "<< endl;
        }
        else cout << "pleer 2 dance! "<< endl;          
        std::this_thread::sleep_for(400ms);
    }
}

int main() {
    Greeting p("ping-pong");
       
    std::vector<std::thread> v;
    std::string pl1="Pleer1";
    std::string pl2="Pleer2";

#ifdef INEER_STOP_TOKEN
    std::stop_source source;
    std::jthread th1(pleer1, source.get_token(), std::ref(pl1));
    std::jthread th2(pleer2, source.get_token(), std::ref(pl2));
#else
    std::jthread th2(pleer2, std::ref(pl2));
    std::jthread th1(pleer1, std::ref(pl1));
#endif

    
    cout << "\n\nPress enter to exit !!\n\n" << endl;
    char ch = getchar();
#ifdef INEER_STOP_TOKEN
    source.request_stop(); //has to be worked without request_stop() on jthreadd desrtr
#endif
    cout << "Just quit." << ch << endl;
}
