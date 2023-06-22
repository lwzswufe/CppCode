#include "publish.h"
#include <stdint.h>
#include <string.h>
#include <x86intrin.h>

/*
g++ -std=c++11  publish.h publish.cpp testPublish.cpp -o publish.out \
-I /usr/local/include/hiredis -lhiredis -levent -lpthread -Wl,-rpath=/usr/local/lib
需要安装libev和libevent两个事件库
*/
void CallBackFun(const char* channel, const char* message, int len)
{
    printf("client recive channel:%s msg:%s len:%d\n", channel, message, len);
};

void GetLocalTimeString(char * str) 
{   // 获取精确到秒的时间
    time_t             timesec; 
    struct tm         *p; 
    time(&timesec); 
    p = localtime(&timesec); 
       
    sprintf(str, "%04d-%02d-%02d %02d:%02d:%02d", 
           1900+p->tm_year, 1+p->tm_mon, p->tm_mday,
           p->tm_hour, p->tm_min, p->tm_sec);    
}

// 获取当前时钟周期
inline uint64_t GetCurrentCycle()
{
    __asm__ __volatile__("" : : : "memory");
    uint64_t r = __rdtsc();
    __asm__ __volatile__("" : : : "memory");
    return r;
}

int main()
{
    const char channel[32]{"Timer"}, key[32]{"test_list"};
    CRedisPublisher pub;
    pub.Init();
    pub.Connect();
    for (int i=0; i<60; ++i)
    {
        char timestr[64];
        memset(timestr, ' ', 64);
        GetLocalTimeString(timestr+32);
        int len = sprintf(timestr, "%lu", GetCurrentCycle());
        timestr[len] = ' ';
        timestr[63] = 0;
        printf("%s\n", timestr);
        pub.Publish(channel, timestr);
        pub.Push(key, timestr);
        usleep(1000 * 1000);
    }
    pub.Disconnect();
    pub.Uninit();
    return 0;
}

