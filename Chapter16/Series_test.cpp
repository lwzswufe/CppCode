#include <iostream>
#include <assert.h>
#include "Series.h"


/*
g++ Series.h Series_test.cpp -o Series_test.exe 
*/

template<typename _Tp>
void print(const Series<_Tp> &ser)
{   
    if (ser.empty())
    {
        std::cout << "Empty Series" << std::endl;
        return;
    }
    for (size_t i=0; i<ser.size() && i<10; i++)
        std::cout << ser.at(i) << ",";
    std::cout << std::endl;
}


int main()
{   

    std::cout << "指定单一值初始化" << std::endl;
    Series<double> ser_d{1.0};
    assert(ser_d.size() == 1 && ser_d[0] == 1.0 && ser_d == 1.0);
    print(ser_d);

    std::cout << "指定多个值初始化" << std::endl;
    Series<int> ser_i(3, 7);
    assert(ser_i.size() == 3 && ser_i[2] == 7);
    print(ser_i);

    std::cout << "修改首元素" << std::endl;
    ser_i.at(0)++;
    print(ser_i);
    assert(ser_i[0] == 8);

    std::cout << "修改指定位置元素" << std::endl;
    ser_i.at(2)++;
    print(ser_i);

    std::cout << "直接对序列变量赋值" << std::endl;
    int a = ser_i[2] + 7;
    ser_i = a;
    print(ser_i);
    assert(ser_i == 15);

    std::cout << "拷贝构造新序列变量" << std::endl;
    Series<int> ser_copy{ser_i(1)};
    assert(ser_copy[0] == ser_i[1]);
    print(ser_i(1));
    return 0;
};