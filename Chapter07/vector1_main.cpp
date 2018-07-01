// #include <iostream>
// using std::cout; using std::endl; using std::ostream;

// #include <string>
// using std::string;

// #include <cstdio>

// 因为头文件vector1.h 已经include 了这些模块 所以在本文件中不用再次include
#include "vector1.h"

int main()
{   
    Vector v1(5.1, 6);
    v1.show();

    Vector v2(3);
    v2.show();
    
    Vector v3;  // 定义了默认构造函数才能使用这种初始化方法

    cout << v1 << endl;
    //v2.dim;

    return 0;
}
