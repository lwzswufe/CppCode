
#include <iostream>
using std::cout; using std::endl;

#include <thread>
using std::thread;
namespace this_thread = std::this_thread;

#include <mutex>
using std::mutex;
using std::recursive_mutex;

#include <string>
using std::string;

#include <chrono>
using std::chrono::steady_clock;                // 硬件时间
using std::chrono::time_point;
using std::chrono::microseconds;

#include <deque>
using std::deque;

/*
g++ deque_with_mutex.cpp -l pthread -o deque_with_mutex.o
*/


mutex cout_mutex;                               // 锁 互斥量
recursive_mutex cout_mutex_r;                   // 可使用 try_lock的互斥量
string global_s;    
deque<string> task_deque{};                     // 任务队列


void task()
{   
    while(true)
    {   
        if(!task_deque.empty() && cout_mutex.try_lock())
        {   
            while (!task_deque.empty())
            {   
                if (task_deque[0] == "stop")
                {   
                    cout_mutex.unlock();
                    goto task_end;
                }
                cout << task_deque[0] << endl;
                task_deque.pop_front();
            }
            cout_mutex.unlock();
        }
    }
    task_end:
    cout << "sub_thread end\n";
}

int main()
{   
    cout << "main start..." << endl;

    thread t_1{task};
    string stop{"stop"};
    char s[20];
    cout << "for start..." << endl;
    for (int i=0; i<100; i++)
    {   
        cout_mutex.lock();             // 阻塞等待 cout_mutex被子线程解锁
        sprintf(s,"word_%03d", i);
        task_deque.push_back(s);
        cout_mutex.unlock();
    }
    task_deque.push_back(stop);
    t_1.join();
}