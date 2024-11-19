#include "include/common_pp.hpp"

using namespace std;
//template<typename T>
class A
{
public:
    A(): a(111){ cout << "ctor  A()"<< endl; };
    A(int a_): a(a_){ cout << "ctor  A(int a_)" << endl; };
    int getValue(){ return a; };
    void setValue(int _a) { a =_a;};
    int operator++() { return ++a;};
    int operator++(int) {return a++; };
protected:
    int a;
private:
};

class B: public A
{
public:
//    B():A(){cout << "ctor  B()" << endl; };
//    B(int a):A(a){cout << "ctor  B(a_)" << endl; };
    int operator--() { return --a;};
    int operator--(int) {return a--; };

protected:
private:

};

void ptrConvert(double* arr){
    // for (int i=0; i<5; i++){
    //     *arr++ *= 2.54;
    // }
    for (int i=0; i<5; i++){
        *arr++ *= 2.54;
    }
}

int main() {
    ProgDeclare p(" =====!!=======cpp private");
    cout << "============= START" << endl;
    double A[5]={10.0, 20, 30, 40, 50};
    //ptrConvert(A);
    double* ptr_a = A;
    for (int i=0; i<5;){
        A[++i] *= 2;
    }
    for (int i=0; i<5; i++){
        cout << "A[" << i << "] = " << A[i] <<endl;
    }
    B a1{};
    B a2{0};
    ++a1;
    ++a2;
    cout << "a1.getValue() = " << a1.getValue() << endl;
    cout << "a2.getValue() = " << a2.getValue() << endl << endl;
//    cout << "a2++ = " << a2++ << endl;
//    cout << "++a2 = " << ++a2 << endl;
//   cout << "a2-- = " << a2-- << endl;
//   cout << "--a2 = " << --a2 << endl;
    //int b=777;
    // B b1;
    // B b2(734);
    // cout << "b1.getValue() = " <<b1.getValue() << endl;
    // cout << "b2.getValue() = " <<b2.getValue() << endl;
   // cout << b2.getValue() << endl;
    
    return 0;
}
