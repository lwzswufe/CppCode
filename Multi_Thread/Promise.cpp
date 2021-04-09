#include <iostream>       // std::cout
using std::cout;
using std::endl;
#include <functional>     // std::ref
#include <thread>         // std::thread
using std::thread;
namespace this_thread = std::this_thread;
#include <future>         // std::promise, std::future
using std::future;
using std::promise;
using std::async;
#include <math.h>
using std::sqrt;
#include <exception>
#include <chrono>
using std::chrono::microseconds;
/*
g++ Promise.cpp -l pthread -o Promise.o
*/

double task (future<double>& fut) 
{   
    cout << "wait input" << endl;
    double x = fut.get();
    if (x < 0)
    {
        // throw std::out_of_range("x < 0");
        throw std::runtime_error("x < 0");
    }
    return sqrt(x);
}

int main()
{
    promise<double> prom;                     // create promise
    future<double> fut = prom.get_future();   // 关联期值
    thread th1 (task, std::ref(fut));         // 传递期值到子线程
    this_thread::sleep_for(microseconds{1000}); 
    cout << "set value" << endl;
    prom.set_value(10);                       // 填充期值 唤醒线程
                                              // (synchronizes with getting the future)
    cout << "return:" << fut.get() << endl;   // 获取返回值
    th1.join();
    thread th2 (task, std::ref(fut));         // 启动线程
   
    try
    {   cout << "set value" << endl;
        prom.set_value(-1.0);                 // 填充值 并唤醒线程
    }
    catch(...)                                // 捕获异常
    {   
        // cout << "Get error from sub thread" << endl;
        std::exception_ptr p = std::current_exception();
        prom.set_exception(std::current_exception());
    }
    try
    { 
        fut.get();
    }
    catch(const std::exception& err)
    {
        cout << "ERROR " << err.what() << endl;
    }
    th2.join();
    return 0;
}