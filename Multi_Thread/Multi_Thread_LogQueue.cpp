#include <iostream>
using std::cout; using std::endl;

#include <atomic>
using std::atomic;

#include <string>
using std::string;

#include <stdio.h> 

#include <chrono>
using std::chrono::steady_clock;                // 硬件时间
using std::chrono::time_point;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::duration;                    // 时间段
using std::chrono::seconds;                     // 秒

#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#include <thread>
using std::thread;
namespace this_thread = std::this_thread;
#else
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#endif
#include "LogQueue.h"
#include <fstream>
using std::ofstream;


int N = 0;
atomic<int> COUNT_PUSH{0};
atomic<int> COUNT_POP{0};

/*
g++ -g -Wall -std=c++11 LogQueue.h LogQueue.cpp Multi_Thread_LogQueue.cpp -o LogQueue.exe
g++ -g -Wall -std=c++11 LogQueue.h LogQueue.cpp Multi_Thread_LogQueue.cpp -o LogQueue.o -lpthread
*/
int rnd()
{   
    return rand() % 8;
} 

string getCurrentTimeStr()
{   
#ifdef _WIN32
    struct timeval tv;    
    mingw_gettimeofday(&tv, NULL);   
    char s[64];
    long seconds = tv.tv_sec % 86400;
    //cout << seconds << ", " << tv.tv_usec << endl;
    sprintf_s(s, "%02d:%02d:%02d.%03d", 8 + seconds / 3600, seconds / 60 % 60, seconds % 60, tv.tv_usec / 1000);
#else
    struct timeval    tv; 
    struct timezone   tz; 
    struct tm         *p; 
    gettimeofday(&tv, &tz);  
    p = localtime(&tv.tv_sec); 
    char s[64];
    sprintf(s, "%02d:%02d:%02d.%03ld", 
            p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec / 1000); 
#endif
    return s;  
}

#ifndef _WIN32
struct thread_info
{
    int thread_id;
    int thread_num;
};
#endif


#ifdef _WIN32
void task_pop(int thread_n)
{   
    printf("%s thread pop start\n", getCurrentTimeStr().c_str());
    thread::id thread_id = this_thread::get_id();                   // 获取线程编号
    steady_clock::time_point time_st = steady_clock::now();
    duration<int64_t> d_s {10};     // 定义周期类型 duration
    ofstream file("a.txt", std::ios::out);
    const char* s;
    for(int i=0; i<N * thread_n;)
    {   
        // int sleep_ms = rnd();
        // this_thread::sleep_for(milliseconds{sleep_ms});             // 沉睡指定时间
        s = QUEUE.pop();
        if (s != NULL)
        {   
            ++COUNT_POP;
            file << s;
            delete[] s;
            i++;
        }
        else
        {
            this_thread::sleep_for(milliseconds{1});
        }
        if (steady_clock::now() - time_st > d_s)
        {
            printf("time out\n");
            break;
        }
    }
    file << std::flush;
    file.close();
    printf("%s thread pop end\n", getCurrentTimeStr().c_str());
}
#else
void *task_pop(void* args)
{   
    printf("%s thread pop start\n", getCurrentTimeStr().c_str());
    thread_info *pinfo = (thread_info *)args;
    int thread_n = pinfo->thread_num;
    int total = N * thread_n;
    bool print_arr[total];
    steady_clock::time_point time_st = steady_clock::now();
    seconds d_s {10};
    ofstream file("a.txt", std::ios::out);
    for(int i=0; i<N * thread_n;)
    {   
        // int sleep_ms = rnd();
        // this_thread::sleep_for(milliseconds{sleep_ms});             // 沉睡指定时间
        const LogInfo* info = GetWriteString();
        if (info != nullptr)
        {   
            ++COUNT_POP;
            file << info->str;
            print_arr[info->info_id] = true;
            ++i;
        }
        else
        {
            // usleep(1);
        }
        if (steady_clock::now() - time_st > d_s)
        {
            printf("time out\n");
            break;
        }
    }
    
    for (int i=0; i<total; i++)
    {
        if (!print_arr[i])
        {   
            char s[64];
            sprintf(s, "info_id:%06d thread:%02d id:%dloss\n", i, i%thread_n, i/thread_n);
            file << s;
        }
    }
    file << std::flush;
    file.close();
    printf("%s thread pop end\n", getCurrentTimeStr().c_str());
    PrintQueue();
}
#endif

#ifdef _WIN32
void task_push(int id)
{   
    
    thread::id thread_id = this_thread::get_id();                   // 获取线程编号
#else
void *task_push(void* args)
{
    thread_info *pinfo = (thread_info *)args;
    // int thread_n = pinfo->thread_num;
    int id = pinfo->thread_id;
    int thread_n = pinfo->thread_num;
#endif
    printf("%s thread push %02d start\n", getCurrentTimeStr().c_str(), id);
    for(int i=0; i<N;)
    {   
        int sleep_ms = rnd();
#ifdef _WIN32
        this_thread::sleep_for(milliseconds{sleep_ms});             // 沉睡指定时间
#else
        usleep(sleep_ms);
#endif  
        char log_level{1};
        LogInfo* info = GetBlankString(log_level);
        info->info_id = i * thread_n + id;
        string str = getCurrentTimeStr();
        sprintf(info->str, "%p_thread_%02d_msg_%04d_%s\n", info, id, i+1, str.c_str());
        ComfirmString(info);
        ++COUNT_PUSH;
        ++i;
    }
    printf("%s thread push %02d end\n", getCurrentTimeStr().c_str(), id);
}

int main(int argc, char** argv)
{   
    if (argc >= 3)
        N = atoi(argv[2]);
    else
        N = 1000;
    int thread_n = 10;
    if (argc >= 2)
        thread_n = atoi(argv[1]);
    printf("thread_n = %d, N = %d\n", thread_n, N);
    LogQueueInitial(512, 128);
#ifdef _WIN32
    thread* thread_arr[thread_n];
    for (int i=0; i<thread_n; i++)
    {   
        thread_arr[i] = new thread{task_push, i+1};
    }
    thread t_0{task_pop, thread_n};
    for (int i=0; i<thread_n; i++)
    {   
        thread_arr[i]->join();
    }
    t_0.join();    
#else
    pthread_t thread_arr[thread_n], t_0;
    thread_info info_arr[thread_n], pop_info{0, thread_n};
    int ret = pthread_create(&t_0, NULL, task_pop, &pop_info);
    for (int i=0; i<thread_n; i++)
    {   
        info_arr[i].thread_id = i;
        info_arr[i].thread_num = thread_n;
        int ret = pthread_create(thread_arr+i, NULL, task_push, info_arr+i);
        if(ret!=0)
        {
            printf("Create pthread_%02d error!\n", i);
            return -1;
        }
    }
    if(ret!=0)
    {
        printf("Create pthread_0 error!\n");
        return -1;
    }
    for (int i=0; i<thread_n; i++)
    {   
        pthread_join(thread_arr[i], NULL);
    }
    pthread_join(t_0, NULL);
#endif
    printf("push:%d pop:%d\n", int(COUNT_PUSH), int(COUNT_POP));   
}