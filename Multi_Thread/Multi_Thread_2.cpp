
#include <iostream>
using std::cout; using std::endl;

#include <unistd.h>
#include <pthread.h>

#include <string>
using std::string;

#include <chrono>
using std::chrono::steady_clock;                // 硬件时间
using std::chrono::time_point;
using std::chrono::microseconds;

/*
pthread库不是Linux系统默认的库，连接时需要使用静态库libpthread.a，所以在线程函数在编译时，
需要连接库函数，如上图    gcc Multi_Thread_2.cpp -o Multi_Thread_2 -lpthread

原型：int  pthread_create（（pthread_t  *thread,  pthread_attr_t  *attr,  void  *（*start_routine）（void  *）,  void  *arg）
用法：#include  <pthread.h>
功能：创建线程（实际上就是确定调用该线程函数的入口点），在线程创建以后，就开始运行相关的线程函数。
说明：thread：线程标识符；
attr：线程属性设置；
start_routine：线程函数的起始地址；
arg：传递给start_routine的参数；
返回值：成功，返回0；出错，返回-1。

attr(属性结构)为pthread_attr_t，它同样在头文件/usr/include/pthread.h中定义。
属性值不能直接设置，须使用相关函数进行操作，初始化的函数为pthread_attr_init，
这个函数必须在pthread_create函数之前调用。属性对象主要包括是否绑定、是否分离、
堆栈地址、堆栈大小、优先级。默认的属性为非绑定、非分离、缺省1M的堆栈、与父进程同样
级别的优先级。 

*/
// 子线程任务函数
void *task(steady_clock::time_point main_st)
{   
    steady_clock::time_point task_st = steady_clock::now();
    steady_clock::duration st_time = task_st - main_st;
    pthread_t pid = pthread_self();
    char s[256];
    sprintf(s,"thread %lu start after %ld ns \n", pid, st_time.count());
    cout << s;
    printf("thread %lu exit\n", pid);
    pthread_exit(0);
}



int main()
{   
    steady_clock::time_point main_st = steady_clock::now();
    pthread_t pid_1;                                                  //pthread_t多线程标识符
    int ret = pthread_create(&pid_1, NULL, task, &main_st);         // 获取线程编号
    if(ret!=0)
    {
        printf("Create pthread error!\n");
        return -1;
    }
    pthread_join(pid_1, NULL);    // 主线程阻塞等待子线程1结束
    //pthread_join(pid_2, NULL);     // 主线程阻塞等待子线程2结束

    steady_clock::duration use_time = steady_clock::now() - main_st;
    char s[50];
    sprintf(s,"main end after %ld ns \n", use_time.count());
    cout << s;
}