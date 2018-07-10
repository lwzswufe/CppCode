
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


mutex cout_mutex;
recursive_mutex cout_mutex_r;
string global_s;

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
    cout << "sub_thread start...\n" << endl;
    string past_word;
    this_thread::sleep_for(microseconds{10}); 
    while(true)
    {   
        this_thread::sleep_for(microseconds{8}); 
        if (cout_mutex_r.try_lock())
        {   
            if (past_word != global_s)
            {
                cout << global_s << endl;
                past_word = global_s;
            }
            cout_mutex_r.unlock();
            if (global_s == "stop")
            {
                cout << "sub thread end" << endl;
                break;
            }
        }  
    }

}

void task_(int num)
{   // 一个需要大量计算的任务
    for (int i=0; i<1000000; i++)
    {
        int j = 1;
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

    task_(123456);

    char s[20];
    int ii = 0;
    string past_word;
    cout << "for start...\n";
    for (int i=0; i<3; i++)
    {
        task_(123456);
        ii++;
        cout_mutex_r.lock();
        sprintf_s(s,"word_%d\n", ii);
        global_s = s;
        cout_mutex_r.unlock();
    }

    cout_mutex_r.lock();
    global_s = "stop";
    cout_mutex_r.unlock();

    t_2.join();
    cout << "main end\n" << endl;
}