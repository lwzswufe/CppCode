
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
using std::chrono::milliseconds;

#include <deque>
using std::deque;

mutex cout_mutex;                               // 锁 互斥量
recursive_mutex cout_mutex_r;                   // 可使用 try_lock的互斥量
string global_s;    
deque<string> task_deque{};                     // 任务队列


/*
g++ Multi_Thread_mutex.cpp -l pthread -o Multi_Thread_mutex.o
*/


void task()
{   
    cout_mutex.lock();
    cout << "sub_thread start...\n";

    this_thread::sleep_for(microseconds{10}); 
    cout << global_s;

    cout_mutex.unlock(); 
    cout << "sub_thread end\n";
}

void task_r()
{   
    string word;
    cout << "sub_thread start...\n" << endl;
    //this_thread::sleep_for(microseconds{10}); 
    while(true)
    {   
        this_thread::sleep_for(microseconds{1}); 
        if (cout_mutex_r.try_lock())
        {   
            if (task_deque.size() > 0)
            {
                word = task_deque.front();
                task_deque.pop_front();
                cout << word;
            }
            else
            {
                word = "empty";
            }
            cout_mutex_r.unlock();
            if (word == "stop")                 // 终止子进程
            {
                cout << "sub thread end" << endl;
                break;
            }
        }  
    }

}

int main()
{   
    cout_mutex.lock();
    global_s = "initial\n";

    cout_mutex.unlock();
    cout << "main start...\n";

    thread t_1{task};

    t_1.join();
    
    cout << "main end\n" << endl;

    cout_mutex_r.lock();
    
    cout_mutex_r.unlock();
    cout << "main start...\n";
    thread t_2{task_r};


    char s[20];
    cout << "for start...\n";
    for (int i=0; i<10; i++)
    {   
        this_thread::sleep_for(milliseconds{1}); 
        cout_mutex_r.lock();
        sprintf(s,"word_%d\n", i);
        task_deque.push_back(s);
        cout_mutex_r.unlock();
    }

    cout << "for loop end\n";

    cout_mutex_r.lock();

    task_deque.push_back("stop");
    cout_mutex_r.unlock();

    t_2.join();
    cout << "main end\n" << endl;
}