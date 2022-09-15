#include "subscribe.h"
#include <stdint.h>
#include <x86intrin.h>

/*
g++ -std=c++11  publish.h subscribe.h publish.cpp subscribe.cpp testSubscribe.cpp -o subscribe.out -I /usr/local/include/hiredis -lhiredis -levent -lpthread
*/

   
// 获取当前时钟周期
inline uint64_t GetCurrentCycle()
{
    __asm__ __volatile__("" : : : "memory");
    uint64_t r = __rdtsc();
    __asm__ __volatile__("" : : : "memory");
    return r;
}

void CallBackFun(const char* channel, const char* message, int len)
{
    static long total_cycle{0}, count{0};
    long diff_cycle{0}, avg_cycle{0};
    if (len > 0)
    {
        long recive_cycle = GetCurrentCycle();
        long send_cycle = atol(message);
        diff_cycle = recive_cycle - send_cycle;
        ++count;
        total_cycle += diff_cycle;
        avg_cycle = total_cycle / count;
    }
    printf("client recive use:%ldcycle avg:%ldcycle channel:%s msg:%s len:%d\n",
           diff_cycle, avg_cycle, channel, message, len);
};


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
    const char channel[32]{"Timer"};
    CRedisSubscriber sub;
    printf("1us=%lucycle\n", GetCPUS());
    sub.Init(CallBackFun);
    sub.Connect();
    sub.Subscribe(channel);
    for (int i=0; i<60; ++i)
    {
        usleep(1000 * 1000);
    }
    sub.Disconnect();
    sub.Uninit();
    return 0;
}

