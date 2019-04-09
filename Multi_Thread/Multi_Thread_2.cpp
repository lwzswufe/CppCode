#include <stdio.h> 

#include <unistd.h>
#include <pthread.h>

#include <string>
using std::string;

#include <sys/time.h>

/*
pthread库不是Linux系统默认的库，连接时需要使用静态库libpthread.a，所以在线程函数在编译时，
需要连接库函数，如上图    g++ Multi_Thread_2.cpp -o Multi_Thread_2 -lpthread

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
double GetTime() 
{   // 获取精确到毫秒的时间
    struct timeval    tv; 
    struct timezone   tz; 
    struct tm         *p; 
       
    gettimeofday(&tv, &tz); 
       
    p = localtime(&tv.tv_sec); 
    double now = p->tm_hour * 10000 + p->tm_min * 60 + 
                 p->tm_sec + tv.tv_usec / 1000000.0; 
    return now;
} 

void *task(void* args)
{   
    pthread_t pid = pthread_self();
    double task_st = GetTime();
    long sleep_usec = (pid % 10) * 1000;
    usleep(sleep_usec);
    double task_ed = GetTime();
    printf("thread %lu start:%.3lf end:%.3lf used:%.3lfs\n", 
            pid, task_st, task_ed, task_ed - task_st);
    pthread_exit(0);
}



int main()
{   
    double main_st = GetTime();
    pthread_t pid_1, pid_2;       // pthread_t多线程标识符
    int ret;
    ret = pthread_create(&pid_1, NULL, task, NULL);         
    if(ret!=0)
    {
        printf("Create pthread1 error!\n");
        return -1;
    }
    ret = pthread_create(&pid_2, NULL, task, NULL);        
    if(ret!=0)
    {
        printf("Create pthread2 error!\n");
        return -1;
    }
    pthread_join(pid_1, NULL);     // 主线程阻塞等待子线程1结束
    pthread_join(pid_2, NULL);     // 主线程阻塞等待子线程2结束

    double main_ed = GetTime();
    printf("main     start:%.3lf end:%.3lf used:%.3lfs\n"
            , main_st, main_ed, main_ed - main_st);
}