#include <queue>
using std::queue;
#include <deque>
using std::deque;
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>
using std::chrono::steady_clock;                // 硬件时间
using std::chrono::time_point;
using std::chrono::system_clock;                // 系统时间
using std::chrono::duration;
using std::chrono::duration_cast;               
using std::chrono::microseconds;                // 毫秒
using std::chrono::milliseconds;                // 微秒
using std::chrono::nanoseconds;                 // 纳秒


/*
g++ -std=c++11 -lpthread TestQueue.cpp -o TestQueue.o
*/
// 交易API请求锁
pthread_mutex_t MUTEX;
// 队列
queue<int> QUEUE{};
// 双端队列
deque<int> DEQUE{};
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
    int recvTime[arrNum]{}, lockTime[arrNum]{}, threshold[arrNum]{0, 1, 5, 25, 125};
    while(MAIN_STATUS)
    {
        while(!QUEUE.empty())
        {
            system_clock::time_point timeStart = GetCurrentTime();
            pthread_mutex_lock(&MUTEX);
            steady_clock::duration lockUseTime = GetCurrentTime() - timeStart;
            int a = QUEUE.front();
            QUEUE.pop();
            size_t len = QUEUE.size();
            pthread_mutex_unlock(&MUTEX);
            steady_clock::duration useTime = GetCurrentTime() - timeStart;
            int64_t useTimeNs = duration_cast<nanoseconds>(useTime).count();
            int64_t lockTimeNs = duration_cast<nanoseconds>(lockUseTime).count();
            for (int i=0; i<arrNum; ++i)
            {
                if (useTimeNs >= threshold[i] * 1000)
                    ++recvTime[i];
                if (lockTimeNs >= threshold[i] * 1000)
                    ++lockTime[i];
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
        printf("%dus lock:%d use:%d\n", threshold[i], lockTime[i], recvTime[i]);
    }
}


void *TaskDeque(void* args)
{   
    int64_t maxTime{0};
    const int arrNum{5};
    int recvTime[arrNum]{}, lockTime[arrNum]{}, threshold[arrNum]{0, 1, 5, 25, 125};
    while(MAIN_STATUS)
    {
        while(!DEQUE.empty())
        {
            system_clock::time_point timeStart = GetCurrentTime();
            pthread_mutex_lock(&MUTEX);
            steady_clock::duration lockUseTime = GetCurrentTime() - timeStart;
            int a = DEQUE[0];
            DEQUE.pop_front();
            size_t len = DEQUE.size();
            pthread_mutex_unlock(&MUTEX);
            steady_clock::duration useTime = GetCurrentTime() - timeStart;
            int64_t useTimeNs = duration_cast<nanoseconds>(useTime).count();
            int64_t lockTimeNs = duration_cast<nanoseconds>(lockUseTime).count();
            for (int i=0; i<arrNum; ++i)
            {
                if (useTimeNs >= threshold[i] * 1000)
                    ++recvTime[i];
                if (lockTimeNs >= threshold[i] * 1000)
                    ++lockTime[i];
            }
            if (useTimeNs > maxTime)
            {
                printf("size:%lu, usetime:%ld locktime:%ld\n", len, useTimeNs, lockTimeNs);
                maxTime = useTimeNs;
            }
        }
        usleep(1);
    }
    printf("test deque exit\n");
    for (int i=0; i<arrNum; ++i)
    {
        printf("%dus lock:%d use:%d\n", threshold[i], lockTime[i], recvTime[i]);
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
        pthread_mutex_lock(&MUTEX); 
        steady_clock::duration lockUseTime = GetCurrentTime() - timeStart;
        QUEUE.push(i);
        pthread_mutex_unlock(&MUTEX);
        int64_t lockTimeNs = duration_cast<nanoseconds>(lockUseTime).count();
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
        printf("push thread %dus lock:%d\n", threshold[i], lockTime[i]);
        lockTime[i] = 0;
    }

    MAIN_STATUS = true;
    pthread_create(&pid, NULL, TaskDeque, NULL);     
    for (int i=0; i<N; ++i)
    {
        system_clock::time_point timeStart = GetCurrentTime();
        pthread_mutex_lock(&MUTEX); 
        steady_clock::duration lockUseTime = GetCurrentTime() - timeStart;
        DEQUE.push_back(i);
        pthread_mutex_unlock(&MUTEX);
        int64_t lockTimeNs = duration_cast<nanoseconds>(lockUseTime).count();
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
        printf("push thread %dus lock:%d\n", threshold[i], lockTime[i]);
        lockTime[i] = 0;
    }
    return 0;
}