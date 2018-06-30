#include <iostream>
using std::cout; using std::endl;

//  extern "C" int add(int, int);       // 链接指示 声明单个函数
extern "C"                              // 链接指示 声明多个函数
{
    int add(int, int);
    int minus(int, int);
    int devide(int, int);
    int mul(int, int);
}
#include "calc.c"


int main()
{
    int a = 7, b = 3, c;
    c = add(a, b);
    cout << "a + b: " << add(a, b) << endl
         << "a - b: " << minus(a, b) << endl
         << "a * b: " << mul(a, b) << endl
         << "a / b: " << divide(a, b) << endl;
}