#include <stdint.h>
#include <x86intrin.h>
#include <stdio.h>
#include <unistd.h>

/*
g++ -std=c++11 getTime6.cpp -o getTime6.out
*/
// 获取当前时钟周期
inline uint64_t GetCurrentCycle()
{
    __asm__ __volatile__("" : : : "memory");
    uint64_t r = __rdtsc();
    __asm__ __volatile__("" : : : "memory");
    return r;
}

// 计算每个微秒的时钟周期数
uint64_t GetCPUS()
{   
    uint64_t r_st = GetCurrentCycle();
    usleep(10 * 1000);
    uint64_t r_ed = GetCurrentCycle();
    return (r_ed - r_st) / 10000;
}

int main()
{
    uint64_t CyclePerUSec = GetCPUS();
    char s[1024];
    uint64_t time_st = GetCurrentCycle();
    sprintf(s, "%d, %s, %.2lf\n", 122, "sdqdq", 265.32);
    uint64_t time_ed = GetCurrentCycle();
    printf("sprintf use %lu Cycle %luns 1us=%luCycle\n", time_ed-time_st, (time_ed-time_st) * 1000 / CyclePerUSec, CyclePerUSec);
    return 0;
}