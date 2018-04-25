#include <iostream>

using namespace std;

int main()
{
	int i = 0;
    int *const p1 = &i;         // 顶层const 指针p1是常量   *const表示指针是常量
    const int ci = 42;          // 顶层const ci是常量       const int 表示指向对象是常量
    const int *p2 = &ci;        // 底层const p2所指对象是const p2不是常量
                                // 指向常量的指针 与指向变量的指针不能互相赋值

    const double pi = 3.14;     // 
    const double *cppi = &pi;   // 指向常量的指针必须 声明为“指向常量”的指针 但其本身不是常量
    double dval = 3.14159;
    const double *const const_pi = &pi;
                                // 指向常量对象的常量指针 *放在const前
                                // 非常量可以转化为常量 反之则不行

    
    cout << "value: " << *cppi << "\naddress: " << cppi << endl;
    cppi = &dval;
    cout << "value: " << *cppi << "\naddress: " << cppi << endl;

    constexpr int mf = 20;     // 常量表达式
    constexpr int limit = mf + 2;
}
