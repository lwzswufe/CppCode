
#include <iostream>
using std::cout; using std::endl;

#include <thread>
using std::thread;
namespace this_thread = std::this_thread;

#include <mutex>
using std::mutex;
using std::recursive_mutex;
using std::unique_lock;
using std::lock_guard;

#include <string>
using std::string;

#include <chrono>
using std::chrono::steady_clock;                // 硬件时间
using std::chrono::time_point;
using std::chrono::microseconds;
using std::chrono::milliseconds;

#include <deque>
using std::deque;

#include <condition_variable>
using std::condition_variable;                  // 条件变量

mutex mut;                                      // 锁 互斥量                        
string global_s;    
deque<string> task_deque{};                     // 任务队列
condition_variable data_cond;                   // 条件变量


/*
g++ ConditionVariable.cpp -l pthread -o ConditionVariable.o
*/


bool fun_condition()
{   
    cout << "fun_cond" << endl;
    return !task_deque.empty();
}

void task()
{   
    cout << "sub_thread start..." << endl;
    //this_thread::sleep_for(microseconds{10});
    int count{0}; 
    while(true)
    {   
        unique_lock<mutex> lm(mut);        // 转移锁的使用权到wait 
        data_cond.wait(lm, fun_condition); // 等待 并锁定
        // cout << " owns lock:" << lm.owns_lock();
        if (task_deque.empty())
        {
            cout << "error cond" << endl;
        }
        cout << " count:" << ++count << " size:" << task_deque.size();
        string word = task_deque.front();
        task_deque.pop_front();
        if (lm.owns_lock())                 // 检查unique_lock类是否拥有锁
        {
            lm.unlock();
            cout << " unlock " << word << endl;
        }
        if (word == "stop")                 // 终止子进程
        {
            cout << "sub thread end" << endl;
            break;
        }
    }
}

int main()
{   
    global_s = "initial\n";
    cout << "main start...\n";
    thread t_2{task};

    char s[20];
    cout << "for start...\n";
    for (int i=0; i<5; i++)
    {   
        lock_guard<mutex> lm(mut);          // 构造时锁定 析构时解锁
        sprintf(s,"word_%d", i);
        task_deque.push_back(s);

        data_cond.notify_one();
        cout << "send word: " << s << " size: "<< task_deque.size() << endl;
        this_thread::sleep_for(milliseconds{20}); 
    }
    this_thread::sleep_for(milliseconds{1000}); 
    cout << "for loop end\n";
    if (true)
    {
        lock_guard<mutex> lm(mut); 
        task_deque.push_back("stop");
        data_cond.notify_one();
    }
    t_2.join();
    cout << "main end\n" << endl;
}