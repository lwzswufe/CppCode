#include <iostream>
#include "Series.h"


/*
g++ Series.h Series_test.cpp -o Series_test.exe 
*/

template<typename _Tp>
void print(Series<_Tp> ser)
{   
    if (ser.empty())
    {
        std::cout << "Empty Series" << std::endl;
        return;
    }
    for (size_t i=0; i<ser.size(); i++)
        std::cout << ser.at(i) << ",";
    std::cout << std::endl;
}


int main()
{   
    Series<double> ser_d;
    print(ser_d);
    Series<int> ser_i(3, 0);
    print(ser_i);
    ser_i.at(0)++;
    print(ser_i);
    ser_i.push_back(6);
    print(ser_i);
    ser_i[1].at(0);
    print(ser_i);
    // print(ser_i[1]);
    return 0;
};