
//
// Method of class in thread
//

#include "include/common_pp.hpp"
 
class A{
    int m_a=7;
public:

    //A(int a= 0): m_a{a} {  
    A(int a= 0) {  
        std::cout << "A constr" << std::endl;
    }
    void Inc() { 
        m_a++; 
        //std::cout << "INC " << std::endl; 
        std::cout << "m_a = " << m_a << std::endl; 
    }
    void Inc2(int i) { 
        m_a+=i; 
        //std::cout << "INC " << std::endl; 
        std::cout << "m_a = " << m_a << std::endl; 
    }
};

int main()
{
    Greeting G("Method of class in thread");
    
    A a(1);
    std::thread th(&A::Inc2, &a, 9);
    th.join();

    return 0;
}