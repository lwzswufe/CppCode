
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

void task(string name, steady_clock::time_point main_st)
{   
    steady_clock::time_point task_st = steady_clock::now();
    steady_clock::duration st_time = task_st - main_st;
    thread::id thread_id = this_thread::get_id();                   // 获取线程编号

    if (name == "one")
        this_thread::sleep_for(microseconds{2});                    // 沉睡指定时间
    else
        this_thread::sleep_until(main_st + microseconds{5});          // 沉睡到指定时刻

    char s[50];
    sprintf_s(s,"thread %d %s start after %d ns \n", thread_id, name.data(), st_time.count());
    cout << s;
}



int main()
{   
    steady_clock::time_point main_st = steady_clock::now();
    thread t_1{task, "one", main_st} , t_2{task, "two", main_st};   // 子线程在这里启动
    
    t_1.join();                                                     // 主线程阻塞等待子线程1结束
    t_2.join();                                                     // 主线程阻塞等待子线程2结束

    steady_clock::duration use_time = steady_clock::now() - main_st;
    char s[50];
    sprintf_s(s,"main end after %d ns \n", use_time.count());
    cout << s;

    int n_thread = thread::hardware_concurrency();
    cout << "max thread num: " << n_thread;
}