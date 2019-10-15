#include <stdio.h>
#include "static_test.h"

// g++ static_test.h, static_test.cpp -o a.exe
int test()
{   
    printf("aa = %d\n", aa);
    aa = 1;
    printf("aa = %d\n", aa);
    return 0;
}