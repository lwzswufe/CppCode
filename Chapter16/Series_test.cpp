#include "Series.h"


/*
g++ Series.h Series.cpp Series_test.cpp -o Series_test.exe 
*/


int main()
{   
    Series<double> ser_d;
    Series<int> ser_i(3, 0);
    return 0;
};