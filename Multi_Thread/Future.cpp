
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
using std::chrono::duration_cast;

#include <deque>
using std::deque;

#include <future>
using std::future;
using std::async;

mutex mut;                                      // 锁 互斥量                        
string global_s;    
deque<string> task_deque{};                     // 任务队列


/*
g++ Future.cpp -l pthread -o Future.o
*/


bool task(const string& word)
{   
    this_thread::sleep_for(microseconds{1000}); 
    cout << word << endl;
    return true;
}

int main()
{   
    global_s = "initial\n";
    cout << "main start...\n";
    deque<future<bool>> DeqFtb{};
    steady_clock::time_point main_st = steady_clock::now();
    int return_i{0};                                    // 获取子线程回报数量
    for (int i=0; i<10; i++)
    {   
        char s[20];
        sprintf(s,"word_%d", i);
        string word{s};
        future<bool> ftb = async(task, word);           // 启动子线程 传递参数
        DeqFtb.push_back(std::move(ftb));               // 必须使用move future不能被复制
        // DeqFtb.push_back(ftb);
        steady_clock::duration use_time = steady_clock::now() - main_st;
        cout << "task_" << i << " start at " << duration_cast<microseconds>(use_time).count() << "us" << endl;
        if (DeqFtb.size() >= 4)                         // 限定最大任务数量
        {
            bool ret = DeqFtb[0].get();                 // 阻塞并等待获取回报
            DeqFtb.pop_front();
            ++return_i;
            use_time = steady_clock::now() - main_st;
            cout << "task_" << return_i << " end at " << duration_cast<microseconds>(use_time).count() << "us" << endl;
        }
    }
    cout << "for loop end\n";
    while (!DeqFtb.empty())                             // 等待剩余回报
    {
        bool ret = DeqFtb[0].get();
        DeqFtb.pop_front();
        ++return_i;
        steady_clock::duration use_time = steady_clock::now() - main_st;
        cout << "task_" << return_i << " end at " << duration_cast<microseconds>(use_time).count() << "us" << endl;
    }
    cout << "main end\n" << endl;
}