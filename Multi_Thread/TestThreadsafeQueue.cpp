#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <memory>
#include <chrono>
using std::chrono::steady_clock;                // 硬件时间
using std::chrono::time_point;
using std::chrono::system_clock;                // 系统时间
using std::chrono::duration;
using std::chrono::duration_cast;               
using std::chrono::microseconds;                // 毫秒
using std::chrono::milliseconds;                // 微秒
using std::chrono::nanoseconds;                 // 纳秒

#include "ThreadsafeQueue.h"

/*
g++ -std=c++11 -lpthread ThreadsafeQueue.h TestThreadsafeQueue.cpp -o TestThreadsafeQueue.o
*/

// 队列
ThreadsafeQueue<int> QUEUE{};
// 主线程状态
bool MAIN_STATUS{true};

system_clock::time_point GetCurrentTime()
{   // 获取当前时间 
    system_clock::time_point sysTime = system_clock::now();
    return sysTime;
}


void *TaskQueue(void* args)
{   
    int64_t maxTime{0};
    const int arrNum{5};
    int recvTime[arrNum]{}, threshold[arrNum]{0, 1, 5, 25, 125};
    while(MAIN_STATUS)
    {
        while(!QUEUE.empty())
        {
            system_clock::time_point timeStart = GetCurrentTime();
            std::shared_ptr<int> a = QUEUE.try_pop();
            if (a == nullptr)
            {
                continue;
            }
            size_t len = QUEUE.size();
            steady_clock::duration useTime = GetCurrentTime() - timeStart;
            int64_t useTimeNs = duration_cast<nanoseconds>(useTime).count();
            for (int i=0; i<arrNum; ++i)
            {
                if (useTimeNs >= threshold[i] * 1000)
                    ++recvTime[i];
            }
            if (useTimeNs > maxTime)
            {
                printf("size:%lu, usetime:%ld\n", len, useTimeNs);
                maxTime = useTimeNs;
            }
        }
        usleep(1);
    }
    printf("test queue exit\n");
    for (int i=0; i<arrNum; ++i)
    {
        printf("%dus use:%d\n", threshold[i], recvTime[i]);
    }
}


int main(int argn, const char** argv)
{   
    int N {100 * 10000};
    if (argn > 1 && atoi(argv[1]) > 0)
        N = atoi(argv[1]);
    printf("set N %d\n", N);
    const int arrNum{5};
    int lockTime[arrNum]{}, threshold[arrNum]{0, 1, 5, 25, 125};
    MAIN_STATUS = true;
    pthread_t pid;
    pthread_create(&pid, NULL, TaskQueue, NULL);     
    for (int i=0; i<N; ++i)
    {   
        system_clock::time_point timeStart = GetCurrentTime();
        QUEUE.push(i);
        steady_clock::duration useTime = GetCurrentTime() - timeStart;
        int64_t lockTimeNs = duration_cast<nanoseconds>(useTime).count();
        for (int i=0; i<arrNum; ++i)
        {
            if (lockTimeNs >= threshold[i] * 1000)
                ++lockTime[i];
        }
    }
    MAIN_STATUS = false;
    pthread_join(pid, NULL);
    for (int i=0; i<arrNum; ++i)
    {
        printf("push thread %dus use:%d\n", threshold[i], lockTime[i]);
        lockTime[i] = 0;
    }
    return 0;
}