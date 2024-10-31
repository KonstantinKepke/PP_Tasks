/**
    Задание 3.this_thread
    В первичном потоке выведите на экран алфавит (‘A’ – ‘Z’) таким образом, чтобы скорость вывода плавно увеличивалась.
 */

// !! FIX TASK name from 1_4 to 1_3 and add loop for char literal 

#include "Task1.h"

int main()
{
    ProgDeclare p("A-Z faster");

    for (char ch = 'A'; ch  < 'Z'; ++ch)
    {
        cout << ch << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(8000 - (100 * (int )ch)));
    }
}
