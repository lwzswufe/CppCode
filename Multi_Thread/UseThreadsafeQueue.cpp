#include <iostream>
using std::cout; using std::endl;

#include <thread>
using std::thread;
namespace this_thread = std::this_thread;

#include <stdio.h>

#include <string>
using std::string;

#include <chrono>
using std::chrono::steady_clock;                // 硬件时间
using std::chrono::time_point;
using std::chrono::microseconds;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
#include "ThreadsafeQueue.cpp"


/*
g++ ThreadsafeQueue.cpp UseThreadsafeQueue.cpp -l pthread -o UseThreadsafeQueue.o
*/

struct  Data
{
    char code[7];
    double price;
};
ThreadsafeQueue<Data> TQD;
int MAX_COUNT{10000};
bool STATUS{false};


void task_output(string name, steady_clock::time_point main_st)
{   
    steady_clock::time_point task_st = steady_clock::now();
    steady_clock::duration use_time = task_st - main_st;
    thread::id thread_id = this_thread::get_id();                      // 获取线程编号
    size_t hid = std::hash<std::thread::id>()(thread_id);
    int count{0}, null_count{0};
    while (count < MAX_COUNT && STATUS)
    {
        std::shared_ptr<Data> pData = TQD.try_pop();
        if (pData != nullptr)
        {
            ++count;
        }
        else
        {
            ++null_count;
        }
    }
    while (!TQD.empty())
    {
        std::shared_ptr<Data> pData = TQD.try_pop();
        if (pData != nullptr)
        {
            ++count;
        }
        else
        {
            ++null_count;
        }
    }
    steady_clock::time_point task_ed = steady_clock::now();
    use_time = task_ed - main_st;
    char s[256];
    sprintf(s,"thread %lu %s end after %lu us count:%d null:%d\n", hid, name.c_str(), 
            duration_cast<microseconds>(use_time).count(), count, null_count);
    cout << "size:" << TQD.size() << endl;
    cout << s;
}

void task_input(string name, steady_clock::time_point main_st)
{   
    steady_clock::time_point task_st = steady_clock::now();
    steady_clock::duration use_time = task_st - main_st;
    thread::id thread_id = this_thread::get_id();                      // 获取线程编号
    size_t hid = std::hash<std::thread::id>()(thread_id);
    int count{0};
    while (count < MAX_COUNT)
    {
        this_thread::sleep_for(microseconds{rand() % 10});            // 沉睡指定时间
        Data data;
        sprintf(data.code, "%06d", rand() % 1000000);
        data.price = rand() % 10000 / 100.00;
        TQD.push(data);
        ++count;
    }
    steady_clock::time_point task_ed = steady_clock::now();
    use_time = task_ed - main_st;
    char s[256];
    sprintf(s,"thread %lu %s end after %lu us count:%d\n", hid, name.c_str(), duration_cast<microseconds>(use_time).count(), count);
    cout << "thread_id:" << thread_id << endl;
    cout << s;
}

int main()
{   
    steady_clock::time_point main_st = steady_clock::now();
    STATUS = true;
    thread t_1{task_input, "input", main_st};                       // 通过初始化线程
    thread t_2{task_output, "output", main_st};                     // 通过初始化线程
    t_1.join();                                                     // 主线程阻塞等待子线程1结束
    this_thread::sleep_for(milliseconds{100}); 
    STATUS = false;
    t_2.join();                                                     // 主线程阻塞等待子线程2结束
    steady_clock::duration use_time = steady_clock::now() - main_st;
    char s[256];
    sprintf(s,"main end after %lu us \n", duration_cast<microseconds>(use_time).count());
    cout << s;

    int n_thread = thread::hardware_concurrency();
    cout << "max thread num: " << n_thread << endl;
}