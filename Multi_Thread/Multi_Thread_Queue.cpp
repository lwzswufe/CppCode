#include <iostream>
using std::cout; using std::endl;

#include <atomic>
using std::atomic;

#include <thread>
using std::thread;
namespace this_thread = std::this_thread;

#include <string>
using std::string;

#include <chrono>
using std::chrono::steady_clock;                // 硬件时间
using std::chrono::time_point;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::duration;                    // 时间段
using std::chrono::seconds;                     // 秒

#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "CircularQueue.h"
#include <fstream>
using std::ofstream;


CircularQueue<const char*> QUEUE(4096);
int N = 0;
atomic<int> COUNT_PUSH{0};
atomic<int> COUNT_POP{0};

/*
g++ CircularQueue.h Multi_Thread_Queue.cpp -o Multi_Thread_Queue.exe
*/
int rnd()
{   
    return rand() % 16;
} 

string getCurrentTimeStr()
{   
    struct timeval tv;    
    mingw_gettimeofday(&tv, NULL);   
    char s[64];
    long seconds = tv.tv_sec % 86400;
    //cout << seconds << ", " << tv.tv_usec << endl;
    sprintf_s(s, "%02d:%02d:%02d.%03d", 8 + seconds / 3600, seconds / 60 % 60, seconds % 60, tv.tv_usec / 1000);
    return s;  
}

void task_pop(int process_n)
{   
    printf("%s thread pop start\n", getCurrentTimeStr().c_str());
    thread::id thread_id = this_thread::get_id();                   // 获取线程编号
    steady_clock::time_point time_st = steady_clock::now();
    duration<int64_t> d_s {10};     // 定义周期类型 duration
    ofstream file("a.txt", std::ios::out);
    const char* s;
    for(int i=0; i<N * process_n;)
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

void task_push(int id)
{   
    printf("%s thread push %02d start\n", getCurrentTimeStr().c_str(), id);
    thread::id thread_id = this_thread::get_id();                   // 获取线程编号
    const char* s;
    for(int i=0; i<N;)
    {   
        int sleep_ms = rnd();
        this_thread::sleep_for(milliseconds{sleep_ms});             // 沉睡指定时间
        char* s = new char[128];
        string str = getCurrentTimeStr();
        sprintf(s, "_thread_%02d_msg_%04d_%s\n", id, i+1, str.c_str());
        if (QUEUE.push(s))
        { 
            ++i;
            ++COUNT_PUSH;
        }
        else
        {
            printf("Queue is full\n");
        }
    }
    printf("%s thread push %02d end\n", getCurrentTimeStr().c_str(), id);
}

int main(int argc, char** argv)
{   
    if (argc >= 3)
        N = atoi(argv[2]);
    else
        N = 10;
    int process_n = 2;
    if (argc >= 2)
        process_n = atoi(argv[1]);
    printf("process_n = %d, N = %d\n", process_n, N);
    thread* thread_arr[process_n];
    for (int i=0; i<process_n; i++)
    {   
        thread_arr[i] = new thread{task_push, i+1};
    }
    thread t_0{task_pop, process_n};
    for (int i=0; i<process_n; i++)
    {   
        thread_arr[i]->join();
    }
    t_0.join();    
    printf("push:%d pop:%d\n", int(COUNT_PUSH), int(COUNT_POP));   
}