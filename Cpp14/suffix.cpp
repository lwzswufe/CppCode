#include <iostream>
#include <chrono>
using std::literals::chrono_literals::operator"" min;

// 万 自定义字面量后缀 _W
// 注意 整数型输入变量类型必须是unsigned long long
int operator"" _W(unsigned long long v)
{
    return v * 10000;
}

// 亿 自定义字面量后缀 _W
// 注意 浮点型输入变量类型必须是long double
double operator"" _Y(long double v)
{
    return v * 10000 * 10000;    
}


int main()
{
    int a = 14_W;
    double b = 2.5_Y;
    auto t1 = 2min;
    // long a = 1023'0000;
    // 二进制字面量c
    int c = 0b10101; 
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    return 0;
}