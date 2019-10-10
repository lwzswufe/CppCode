#include<stdio.h>

static int a = 1;           // 作用域本文件内
struct Clock
{
    int h;
    int m;
    int s;
};
static Clock clock;
static int arr[3];

int main()
{   
    printf("a = %d\n", a);
    a += 1;
    printf("a = %d\n", a);
    clock = {1, 2, 3};
    printf("clock: %02d:%02d:%02d\n", clock.h, clock.m, clock.s);
    arr = {1, 2, 3};
    printf("arr:%d, %d, %d\n", arr[0], arr[1], arr[2]);
    return 0;
}