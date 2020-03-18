#include <stdio.h>
#include <math.h>
#include <iostream>
int main()
{   
    double d = nan("NAN");
    printf("d = %lf  d * 1 = %lf d * 0 = %lf d + 1 = %lf\n", d, d * 1, d * 0, d + 1);
    std::cout << "d: " << std::hex << d << std::endl; 
    printf("d = %x\n", d);
    return 0;
}