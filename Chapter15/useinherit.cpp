#include "inherit.h"

#include <cstddef>
using std::size_t;

#include <iostream>
using std::ostream; using std::endl; 
using std::cout;

int main()
{
    Base base_0, base_1("No_1");
    A base_a;
    B base_b;
    C base_c;
    print(base_0);
    print(base_1); 
    print(base_a);
    cout << base_a.cls_name << endl;
    //cout << base_a.sum(1, 2, 3) << endl;  // A 仅重载了sum(a, b)版本的sum 所以这里调用会失败
    cout << base_a.sum(1, 2) << endl;
    cout << base_b.sum(1, 2, 3) << endl;    // B 共有的继承了base 这里调用的是Base版本的sum
    cout << base_c.sum(1, 2) << endl;       // C 私有的继承了base 但是在public部分using Base::std 这里调用的是Base版本的sum
    cout << base_c.sum(1, 2, 3) << endl;

    Base* bptr_0 = &base_0;
    Base* bptr_b = &base_b;

    using PMfi = int(Base::*)(int, int);    // 成员函数指针 指向类的相对位置
    PMfi pf = &Base::sum;                   // 初始化指针
    cout << (base_0.*pf)(2, 3) << endl;     // 调用基类函数
    cout << (base_a.*pf)(2, 3) << endl;     // 调用派生类重构后的函数
    cout << (bptr_0->*pf)(2, 3) << endl;    // 通过类指针调用成员函数指针
    cout << (bptr_b->*pf)(2, 3) << endl; 

    using PM = const string Base::*;        // 数据成员指针 指向类的相对位置
    PM pm = &Base::name;
    cout << base_0.*pm << endl;
    cout << base_a.*pm << endl;
    cout << bptr_0->*pm << endl;            // 通过类指针调用数据成员
    cout << bptr_b->*pm << endl; 
    return 0;
}