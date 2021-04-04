
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
using std::chrono::duration_cast;
using std::chrono::milliseconds;


/*
g++ Multi_Thread_1.cpp -l pthread -o Multi_Thread_1.o
*/


void task(string name, steady_clock::time_point main_st)
{   
    steady_clock::time_point task_st = steady_clock::now();
    steady_clock::duration use_time = task_st - main_st;
    thread::id thread_id = this_thread::get_id();                      // 获取线程编号
    size_t hid = std::hash<std::thread::id>()(thread_id);
    char s[256];
    sprintf(s,"thread %lu %s start after %lu us \n", hid, name.c_str(), duration_cast<microseconds>(use_time).count());
    cout << s;
    this_thread::sleep_for(milliseconds{2});                      // 沉睡指定时间
    steady_clock::time_point task_ed = steady_clock::now();
    use_time = task_ed - main_st;
    sprintf(s,"thread %lu %s end after %lu us \n", hid, name.c_str(), duration_cast<microseconds>(use_time).count());
    cout << "thread_id:" << thread_id << endl;
    cout << s;
}


class Task
{
public:
    Task(const string& name);
    void run(steady_clock::time_point main_st);
private:
    string _name{"undefine"};
};


Task::Task(const string& name)
{
    _name = name;
}

void Task::run(steady_clock::time_point main_st)
{
    steady_clock::time_point task_st = steady_clock::now();
    steady_clock::duration use_time = task_st - main_st;
    thread::id thread_id = this_thread::get_id();                      // 获取线程编号
    size_t hid = std::hash<std::thread::id>()(thread_id);
    char s[256];
    sprintf(s,"thread %lu %s start after %lu us \n", hid, _name.c_str(), duration_cast<microseconds>(use_time).count());
    cout << s;
    this_thread::sleep_until(main_st + milliseconds{5});          // 沉睡到指定时刻
    steady_clock::time_point task_ed = steady_clock::now();
    use_time = task_ed - main_st;
    sprintf(s,"thread %lu %s end after %lu us \n", hid, _name.c_str(), duration_cast<microseconds>(use_time).count());
    cout << "thread_id:" << thread_id << endl;
    cout << s;
}


int main()
{   
    steady_clock::time_point main_st = steady_clock::now();
    Task task_obj{"class   "};
    thread t_1{task, "function", main_st};          // 通过函数初始化线程
    thread t_2{&Task::run, &task_obj, main_st};     // 通过类初始化线程
    
    t_1.join();                                                     // 主线程阻塞等待子线程1结束
    t_2.join();                                                     // 主线程阻塞等待子线程2结束

    steady_clock::duration use_time = steady_clock::now() - main_st;
    char s[256];
    sprintf(s,"main end after %lu us \n", duration_cast<microseconds>(use_time).count());
    cout << s;

    int n_thread = thread::hardware_concurrency();
    cout << "max thread num: " << n_thread << endl;
}