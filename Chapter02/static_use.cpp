#include<stdio.h>
#include "static_test.h"

// g++ static_test.h static_test.cpp static_use.cpp -o static_use.exe
// 头文件声明的静态变量 可以被其他文件引用
static int a = 1;           // 作用域本文件内
struct Clock
{
    int h;
    int m;
    int s;
};
static Clock clock;
static int arr[3] = {1, 2, 3};

int main()
{   
    test();
    printf("aa = %d\n", aa);
    printf("a = %d\n", a);
    a += 1;
    printf("a = %d\n", a);
    clock = {1, 2, 3};
    printf("clock: %02d:%02d:%02d\n", clock.h, clock.m, clock.s);
    arr[1] = 0;
    printf("arr:%d, %d, %d\n", arr[0], arr[1], arr[2]);
    return 0;
}