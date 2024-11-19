/**
 * 1.1. Запуск потоков с ожиданием завершения
 *   - 1.а Последовательно запускаем потоки. Очередной поток запускаем только после завершения текущего  Измерьте время работы фрагмента.
 */

#include "Task2.h"


void th1(){
    ProgDeclare th("th() func");
    


}

int main() {
    ProgDeclare p("1_task - make files content uppercase");
       
    std::thread thread_1(th1);
    thread_1.join();
    return 0;
}
