/**
    Задание 3.this_thread
    В первичном потоке выведите на экран алфавит (‘A’ – ‘Z’) таким образом, чтобы скорость вывода плавно увеличивалась.
 */

#include "Task1.h"

int main() {
    ProgDeclare p("A-Z faster");
      
    char ch = 'A';

    for (int i=0 ; i < 26; ++i){
        cout << ch++ << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1500-(100*i))); 
    }
}
