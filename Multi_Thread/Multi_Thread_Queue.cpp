#include <iostream>
using std::cout; using std::endl;

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

#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "CircularQueue.h"
#include <fstream>
using std::ofstream;


CircularQueue<const char*> QUEUE(128);
#define N 1000


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

void task_pop()
{   
    printf("%s thread pop start\n", getCurrentTimeStr().c_str());
    thread::id thread_id = this_thread::get_id();                   // 获取线程编号
    ofstream file("a.txt");
    const char* s;
    for(int i=0; i<N; i++)
    {   
        int sleep_ms = rnd();
        this_thread::sleep_for(milliseconds{sleep_ms});             // 沉睡指定时间
        while(QUEUE.pop(s))
        {
            file << getCurrentTimeStr() << s;
            delete[] s;
        }
    }
    this_thread::sleep_for(milliseconds{1000});  
    while(QUEUE.pop(s))
    {
        file << getCurrentTimeStr() << s;
    }
    file.close();
    printf("%s thread pop end\n", getCurrentTimeStr().c_str());
}

void task_push(int id)
{   
    printf("%s thread push %02d start\n", getCurrentTimeStr().c_str(), id);
    thread::id thread_id = this_thread::get_id();                   // 获取线程编号
    const char* s;
    for(int i=0; i<N; i++)
    {   
        int sleep_ms = rnd();
        this_thread::sleep_for(milliseconds{sleep_ms});             // 沉睡指定时间
        char* s = new char[64];
        string str = getCurrentTimeStr();
        sprintf(s, "_thread_%02d_msg_%04d_%s\n", id, i+1, str.c_str());
        QUEUE.push(s);
    }
    printf("%s thread push %02d end\n", getCurrentTimeStr().c_str(), id);
}

int main()
{   
    thread t_1{task_push, 1}, t_2{task_push, 2} , t_3{task_pop};        
    t_1.join(); 
    t_2.join();
    t_3.join();
}